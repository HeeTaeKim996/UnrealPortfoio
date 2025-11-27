


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





void UR1AbilityTask::OnAbilitySuccess(FGameplayTag InTag)
{
}

void UR1AbilityTask::OnAbilityCancel(FGameplayTag InTag)
{
}

void UR1AbilityTask::OnTraceHit(FMeleeHitInfo MeleeHitInfo)
{
}
