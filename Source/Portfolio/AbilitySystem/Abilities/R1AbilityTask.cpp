


#include "AbilitySystem/Abilities/R1AbilityTask.h"
#include "Character/R1Character.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"

void UR1AbilityTask::Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter)
{
	WeakAbility = InAbility;
	WeakCharacter = InCharacter;
	AbilityTag = InAbility->AbilityTags.First();

	InCharacter->GAS_OnAbilitySuccess.AddDynamic(this, &UR1AbilityTask::OnAbilitySuccess);
	InCharacter->GAS_OnTraceHit.AddDynamic(this, &UR1AbilityTask::OnTraceHit);
	InCharacter->GAS_OnAbilityCancel.AddDynamic(this, &UR1AbilityTask::OnAbilityCancel);

	
}

void UR1AbilityTask::Activate()
{
	Super::Activate();
}

void UR1AbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UR1AbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	if (WeakCharacter.IsValid())
	{
		AR1Character* R1Character = WeakCharacter.Get();
		R1Character->GAS_OnAbilitySuccess.RemoveDynamic(this, &UR1AbilityTask::OnAbilitySuccess);
		R1Character->GAS_OnTraceHit.RemoveDynamic(this, &UR1AbilityTask::OnTraceHit);
		R1Character->GAS_OnAbilityCancel.RemoveDynamic(this, &UR1AbilityTask::OnAbilityCancel);
	}
	
}

void UR1AbilityTask::OnAbilitySuccess(FAbilitySuccessInfo SucessInfo)
{
	AbilitySuccess(MoveTemp(SucessInfo));
}

void UR1AbilityTask::OnAbilityCancel(FAbilityCancelInfo CancelInfo)
{
	AbilityCancel(MoveTemp(CancelInfo));
}

void UR1AbilityTask::OnTraceHit(FMeleeHitInfo MeleeHitInfo)
{
	TraceHit(MoveTemp(MeleeHitInfo));
}




bool UR1AbilityTask::AbilitySuccess(FAbilitySuccessInfo SuccessInfo)
{
	if (AbilityTag != SuccessInfo.AbilityTag) return false;

	return true;
}

bool UR1AbilityTask::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	if (AbilityTag != CancelInfo.AbilityTag) return false;

	return true;
}

bool UR1AbilityTask::TraceHit(FMeleeHitInfo MeleeHitInfo)
{
	if (AbilityTag != MeleeHitInfo.Ability) return false;

	return true;
}

