


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
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}



void UR1GameplayAbility::PlayMontage(UAnimMontage* Montage, FName SectionName)
{
	UAnimInstance* AnimInstance = GetActorInfo().GetAnimInstance();
	if (!AnimInstance || !Montage)
	{
		EndAbilityCancel();
		return;
	}

	float duration = AnimInstance->Montage_Play(Montage, 1.f);
	if (duration < 0.f)
	{
		EndAbilityCancel();
		return;
	}
	if (SectionName != "")
	{
		AnimInstance->Montage_JumpToSection(SectionName);
	}
	

	FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Montage);
	if (!MontageInstance)
	{
		EndAbilityCancel();
		return;
	}

	MontageInstance->OnMontageEnded.Unbind();

	MontageInstance->OnMontageEnded.BindUObject(this, &UR1GameplayAbility::OnMontageEnded);
}

void UR1GameplayAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	if (bInterruped)
	{
		EndAbilityCancel();
	}
	else
	{
		EndAbilitySuccess();
	}
}

