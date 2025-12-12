


#include "AbilitySystem/Abilities/AttackAbility.h"
#include "Character/R1Character.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "GameplayEffect.h"

void UAttackAbilityTask::Activate()
{
	Super::Activate();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (!R1Character)
	{
		Cast<UR1GameplayAbility>(Ability)->EndAbilityCancel();
		return;
	}

	R1Character->GAS_OnAttackSucceed.AddDynamic(this, &UAttackAbilityTask::OnAttackSucceed);
}

void UAttackAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UAttackAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->GAS_OnAttackSucceed.RemoveDynamic(this, &UAttackAbilityTask::OnAttackSucceed);
	}
}

void UAttackAbilityTask::OnAttackSucceed(const FMeleeHitInfo& MeleeHitInfo)
{
	AttackSucceed(MeleeHitInfo);
}

bool UAttackAbilityTask::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo)
{
	if (Ability->AbilityTags.HasTag(MeleeHitInfo.Ability) == false) return false;

	AActor* HitActor = MeleeHitInfo.HitResult.GetActor();
	AR1Character* HItCharacter = Cast<AR1Character>(HitActor);
	if (HItCharacter == nullptr) return false;


	AActor* SourceActor = GetAvatarActor();
	AR1Character* SourceCharacter = Cast<AR1Character>(SourceActor);
	UR1AbilitySystemComponent* SourceASC
		= Cast<UR1AbilitySystemComponent>(SourceCharacter->GetAbilitySystemComponent());

	UR1AbilitySystemComponent* TargetASC
		= Cast<UR1AbilitySystemComponent>(HItCharacter->GetAbilitySystemComponent());
	UAttackAbility* AttackAbility = Cast<UAttackAbility>(Ability);

	TSubclassOf<UGameplayEffect> GE = AttackAbility->AttackInfos[MeleeHitInfo.Protocol].GE;
	if (TargetASC && GE && SourceASC)
	{
		FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
		EffectContext.AddHitResult(MeleeHitInfo.HitResult);
		EffectContext.AddInstigator(SourceActor, SourceActor);

		FGameplayEffectSpecHandle SpecHandle =
			SourceASC->MakeOutgoingSpec(GE, 1, EffectContext);
		
		FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
		Spec->SetSetByCallerMagnitude(R1Tags::Data_GESpec_AttackCoefficient,
			AttackAbility->AttackInfos[MeleeHitInfo.Protocol].AttackCoefficient);
		Spec->SetSetByCallerMagnitude(R1Tags::Data_GESpec_Impact,
			AttackAbility->AttackInfos[MeleeHitInfo.Protocol].Impact);

		TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	}


	return true;
}

UAttackAbility::UAttackAbility()
	: Super()
{

}
