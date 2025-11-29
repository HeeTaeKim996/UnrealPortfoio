


#include "AbilitySystem/Abilities/R1AbilityTask.h"
#include "Character/R1Character.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"

void UR1AbilityTask123::Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter)
{
	WeakAbility = InAbility;
	WeakCharacter = InCharacter;
	AbilityTag = InAbility->AbilityTags.First();

	InCharacter->GAS_OnAbilitySuccess.AddDynamic(this, &UR1AbilityTask123::OnAbilitySuccess);
	InCharacter->GAS_OnTraceHit.AddDynamic(this, &UR1AbilityTask123::OnTraceHit);
	InCharacter->GAS_OnAbilityCancel.AddDynamic(this, &UR1AbilityTask123::OnAbilityCancel);

	
}

void UR1AbilityTask123::Activate()
{
	Super::Activate();
}

void UR1AbilityTask123::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UR1AbilityTask123::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	if (WeakCharacter.IsValid())
	{
		AR1Character* R1Character = WeakCharacter.Get();
		R1Character->GAS_OnAbilitySuccess.RemoveDynamic(this, &UR1AbilityTask123::OnAbilitySuccess);
		R1Character->GAS_OnTraceHit.RemoveDynamic(this, &UR1AbilityTask123::OnTraceHit);
		R1Character->GAS_OnAbilityCancel.RemoveDynamic(this, &UR1AbilityTask123::OnAbilityCancel);
	}
	
}

void UR1AbilityTask123::ClearAbility()
{
	if (WeakAbility.IsValid())
	{
		WeakAbility.Get()->EndAbilitySuccess();
	}
	EndTask();
}

void UR1AbilityTask123::OnAbilitySuccess(FAbilitySuccessInfo SucessInfo)
{
	AbilitySuccess(MoveTemp(SucessInfo));
}

void UR1AbilityTask123::OnAbilityCancel(FAbilityCancelInfo CancelInfo)
{
	AbilityCancel(MoveTemp(CancelInfo));
}

void UR1AbilityTask123::OnTraceHit(FMeleeHitInfo MeleeHitInfo)
{
	TraceHit(MoveTemp(MeleeHitInfo));
}




bool UR1AbilityTask123::AbilitySuccess(FAbilitySuccessInfo SuccessInfo)
{
	if (AbilityTag != SuccessInfo.AbilityTag) return false;

	return true;
}

bool UR1AbilityTask123::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	if (CancelInfo.Cause == CancelCause::ShutDown)
	{
		ClearAbility();
		return false;
	}

	return true;
}

bool UR1AbilityTask123::TraceHit(FMeleeHitInfo MeleeHitInfo)
{
	if (AbilityTag != MeleeHitInfo.Ability) return false;

	return true;
}

