


#include "AbilitySystem/Abilities/Action/Death/DeathAbility.h"
#include "Structures/FNameContainer.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

void UDeathAbilityTask::Activate()
{
	Super::Activate();
}

void UDeathAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UDeathAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}







UDeathAbility::UDeathAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Dead);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = R1Tags::Ability_Dead;

	AbilityTriggers.Add(TriggerData);
}

bool UDeathAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	InSectionName = Cast<UFNameContainer>(TriggerEventData->OptionalObject)->Name;

	// ※ Before Activate ActionAbility, Set SectionName
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UDeathAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



void UDeathAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	Super::OnMontageEnded(Montage, bInterruped);

	DebugMessage("DeathAbility.cpp : Temp Montage End Check");
}
