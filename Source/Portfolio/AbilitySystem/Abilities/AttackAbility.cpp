


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

	R1Character->GAS_OnTraceHit.AddDynamic(this, &UAttackAbilityTask::OnTraceHit);
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
		R1Character->GAS_OnTraceHit.RemoveDynamic(this, &UAttackAbilityTask::OnTraceHit);
	}
}

void UAttackAbilityTask::OnTraceHit(FMeleeHitInfo MeleeHitInfo)
{
}
