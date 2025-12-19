


#include "AbilitySystem/Abilities/AttackAbility.h"
#include "Character/R1Character.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Structures/TraceHitInfo.h"
#include "Kismet/GameplayStatics.h"


void UAttackAbilityTask::Activate()
{
	Super::Activate();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->Delegate_OnTraceHit.AddDynamic(this, &UAttackAbilityTask::OnAttackSucceed);
		R1Character->Delegate_GAMultiDelegate.AddDynamic(this, &UAttackAbilityTask::OnDelegate_GAMultiDelegate);
	}

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
		R1Character->Delegate_OnTraceHit.RemoveDynamic(this, &UAttackAbilityTask::OnAttackSucceed);
		R1Character->Delegate_GAMultiDelegate.RemoveDynamic(this, &UAttackAbilityTask::OnDelegate_GAMultiDelegate);
	}
}

void UAttackAbilityTask::OnAttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	AttackSucceed(MeleeHitInfo, TraceHitInfo);
}

void UAttackAbilityTask::OnDelegate_GAMultiDelegate(const FGameplayTag& InTag)
{
	if (InTag != R1Tags::Event_GAS_AttackSoundStart) return;

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	UAttackAbility* AttackAbility = Cast<UAttackAbility>(Ability);
	if (AttackAbility && AttackAbility->SoundInfo.SoundBase && R1Character)
	{
		const FSoundInfo& SoundInfo = AttackAbility->SoundInfo;

		AttackAbility->AttackSoundComponent = UGameplayStatics::SpawnSoundAttached(SoundInfo.SoundBase, 
			R1Character->GetRootComponent(), NAME_None, FVector::ZeroVector, EAttachLocation::KeepRelativeOffset, false, 
			SoundInfo.Volume, SoundInfo.StartTime);
	}
}

bool UAttackAbilityTask::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Ability->AbilityTags.HasTag(MeleeHitInfo.Ability) == false) return false;

	AActor* HitActor = MeleeHitInfo.HitResult.GetActor();
	AR1Character* HItCharacter = Cast<AR1Character>(HitActor);
	if (HItCharacter == nullptr) return false;

	if (TraceHitInfo.TraceHitResult == ETraceHitResult::Hit)
	{
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
	}


	return true;
}










UAttackAbility::UAttackAbility()
	: Super()
{

}

bool UAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AttackSoundComponent && bWasCancelled)
	{
		AttackSoundComponent->FadeOut(0.1f, 0.f);
		AttackSoundComponent = nullptr;
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
