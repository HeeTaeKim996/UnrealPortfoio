


#include "AbilitySystem/Abilities/Action/HitReact/HitReactAbility.h"
#include "Structures/FNameContainer.h"

void UHitReactAbilityTask::Activate()
{
	Super::Activate();
}

void UHitReactAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
}

void UHitReactAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}












UHitReactAbility::UHitReactAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_HitReact_Base);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = R1Tags::Ability_Action_HitReact_Base;
	AbilityTriggers.Add(TriggerData);
}

bool UHitReactAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UHitReactAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	InSectionName = Cast<UFNameContainer>(TriggerEventData->OptionalObject)->Name;

	// ※ Before Activate ActionAbility, Set SectionName
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHitReactAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
