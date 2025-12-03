


#include "AbilitySystem/Abilities/AttackAbility.h"
#include "Character/R1Character.h"

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

void UAttackAbilityTask::OnAttackSucceed(FMeleeHitInfo MeleeHitInfo)
{
	AttackSucceed(MoveTemp(MeleeHitInfo));
}

bool UAttackAbilityTask::AttackSucceed(FMeleeHitInfo MeleeHitInfo)
{
	if (Ability->AbilityTags.HasTag(MeleeHitInfo.Ability) == false) return false;

	{ // Will be reversed with AttributeSet Info
		AActor* HitActor = MeleeHitInfo.HitActor;
		AR1Character* HItCharacter = Cast<AR1Character>(HitActor);
		if (HItCharacter == nullptr) return false;

		HItCharacter->OnDamage(20, Cast<AR1Character>(GetAvatarActor()));
	}

	

	return true;
}
