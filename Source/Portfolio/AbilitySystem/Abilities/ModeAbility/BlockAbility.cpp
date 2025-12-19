


#include "AbilitySystem/Abilities/ModeAbility/BlockAbility.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

void UBlockAbilityTask::Activate()
{
	Super::Activate();
}

void UBlockAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UBlockAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
















UBlockAbility::UBlockAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityTags.AddTagFast(R1Tags::Ability_Mode_Blocking);

	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Mode_Blocking);
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_MotionState_UpperAngleSplit);
}


bool UBlockAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, 
	OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UBlockAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UBlockAbilityTask* Task = UAbilityTask::NewAbilityTask<UBlockAbilityTask>(this);
	Task->ReadyForActivation();


}

void UBlockAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
