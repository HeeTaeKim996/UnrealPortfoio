


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

bool UBlockAbilityTask::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	Super::AbilityCancel(CancelInfo);

	return true;
}
















UBlockAbility::UBlockAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StateTag = R1Tags::State_Mode_Blocking;
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


	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("BlockStart"));
}

void UBlockAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("BlockEnd"));
}
