


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
		PlayMontage(R1ASC, PlayingMontage, InSectionName);
	}
	
}

void UActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	

}

void UActionAbility::PlayMontage(UR1AbilitySystemComponent* R1ASC, UAnimMontage* Montage, FName SectionName)
{
	if (R1ASC == nullptr || Montage == nullptr)
	{
		EndAbilityCancel();
		return;
	}

	float duration = R1ASC->PlayMontage(this, GetCurrentActivationInfo(), Montage, 1.f, SectionName, 0.f);
	if (duration < 0.f)
	{
		EndAbilityCancel();
		return;
	}


	UAnimInstance* AnimInstance = GetActorInfo().GetAnimInstance();
	FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Montage);
	if (!MontageInstance)
	{
		EndAbilityCancel();
		return;
	}

	MontageInstance->OnMontageEnded.Unbind();

	MontageInstance->OnMontageEnded.BindUObject(this, &UActionAbility::OnMontageEnded);
}

void UActionAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	if(bInterruped == false)
	{
		EndAbilitySuccess();
	}
	// ※ if bInterruppted == true -> Taht should be ASC Call Cancel This Ability
}
