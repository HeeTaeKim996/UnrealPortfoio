


#include "AbilitySystem/Abilities/MontageAbility.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"


void UMontageAbilityTask::Activate()
{
	Super::Activate();
}

void UMontageAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UMontageAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}










UMontageAbility::UMontageAbility()
	: Super()
{
}

bool UMontageAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UMontageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (ASC)
	{
		PlayMontage(ASC, PlayingMontage, InSectionName);
	}
}

void UMontageAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMontageAbility::PlayMontage(UR1AbilitySystemComponent* R1ASC, UAnimMontage* Montage, FName SectionName)
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
	MontageInstance = AnimInstance->GetActiveInstanceForMontage(Montage);
	if (!MontageInstance)
	{
		EndAbilityCancel();
		return;
	}

	MontageInstance->OnMontageEnded.Unbind();
	MontageInstance->OnMontageEnded.BindUObject(this, &UMontageAbility::OnMontageEnded);

	MontageInstance->OnMontageBlendingOutStarted.Unbind();
	MontageInstance->OnMontageBlendingOutStarted.BindUObject(this, &UMontageAbility::OnMontageBlendingOutStarted);
}

void UMontageAbility::OnMontageBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted)
{

}

void UMontageAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{

}
