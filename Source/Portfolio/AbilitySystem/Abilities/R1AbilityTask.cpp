


#include "AbilitySystem/Abilities/R1AbilityTask.h"
#include "Character/R1Character.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"

void UR1AbilityTask::Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter)
{
	WeakAbility = InAbility;
	WeakCharacter = InCharacter;
	AbilityTag = InAbility->AbilityTags.First();

	InCharacter->OnAbilitySuccess.AddDynamic(this, &UR1AbilityTask::OnAbilitySuccess);
	InCharacter->OnTraceHit.AddDynamic(this, &UR1AbilityTask::OnTraceHit);

	
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
		R1Character->OnAbilitySuccess.RemoveDynamic(this, &UR1AbilityTask::OnAbilitySuccess);
		R1Character->OnTraceHit.RemoveDynamic(this, &UR1AbilityTask::OnTraceHit);
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
