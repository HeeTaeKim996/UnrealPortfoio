


#include "AbilitySystem/Abilities/ActionAbility.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

void UActionAbilityTask::Activate()
{
	Super::Activate();
	
}

void UActionAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UActionAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}







UActionAbility::UActionAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UR1AbilitySystemComponent* R1ASC = Cast<UR1AbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (R1ASC)
	{
		PlayMontage(R1ASC, PlayingMontage, SectionName);
	}
	
}

void UActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	

}
