


#include "AbilitySystem/Abilities/Action/HitReact/GetupAbility.h"
#include "Structures/FNameContainer.h"

void UGetupAbilityTask::Activate()
{
	Super::Activate();
}

void UGetupAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

}

void UGetupAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

}








UGetupAbility::UGetupAbility()
	: Super()
{
	AbilityTags.AddTagFast(R1Tags::Ability_Action_HitReact_Getup);
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_HitReact_Getup);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = R1Tags::Ability_Action_HitReact_Getup;
	AbilityTriggers.Add(TriggerData);
}

bool UGetupAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UGetupAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	InSectionName = Cast<UFNameContainer>(TriggerEventData->OptionalObject)->Name;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGetupAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
