


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







UActionAbility::UActionAbility()
	: Super()
{

}

void UActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);	
}

void UActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	

}



void UActionAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	Super::OnMontageEnded(Montage, bInterruped);

	if(bInterruped == false)
	{
		EndAbilitySuccess();
	}
	// ※ if bInterruppted == true -> Taht should be ASC Call Cancel This Ability
}
