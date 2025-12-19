


#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

/* Ability Task */
void UR1AbilityTask::SuccessAbility()
{
	Cast<UR1GameplayAbility>(Ability)->EndAbilitySuccess();
}

void UR1AbilityTask::CancelAbility()
{
	Cast<UR1GameplayAbility>(Ability)->EndAbilityCancel();
}















/* Ability */
UR1GameplayAbility::UR1GameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UR1GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UR1GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (bWasCancelled == true)
	{
		MontageStop(1.f); // Stop Playing Montage if This Ability Invoked Montage. This must be prior to Super's EndAbility
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



