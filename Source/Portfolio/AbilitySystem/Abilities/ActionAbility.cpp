


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

	PlayMontage(PlayingMontage, SectionName);
}

void UActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (ActorInfo)
	{
		UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
		ASC->ClearRoot(R1Tags::State_Action);


		AR1Character* R1Character = Cast<AR1Character>(ActorInfo->AvatarActor);
		if (R1Character)
		{
			R1Character->ToLoco();
		}
	}

}
