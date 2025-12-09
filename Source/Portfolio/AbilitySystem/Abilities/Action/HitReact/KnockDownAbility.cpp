


#include "AbilitySystem/Abilities/Action/HitReact/KnockDownAbility.h"
#include "Structures/FNameContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

void UKncokDownAbilityTask::Activate()
{
	Super::Activate();
}

void UKncokDownAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UKncokDownAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}








UKnockDownAbility::UKnockDownAbility()
	: Super()
{
	AbilityTags.AddTagFast(R1Tags::Ability_Action_HitReact_Knockdown);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = R1Tags::Ability_Action_HitReact_Knockdown;
	AbilityTriggers.Add(TriggerData);
}

bool UKnockDownAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UKnockDownAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	InSectionName = Cast<UFNameContainer>(TriggerEventData->OptionalObject)->Name;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	ASC->AddLooseGameplayTag(R1Tags::Ability_Action_HitReact_Knockdown);

	FOnMontageBlendingOutStarted& OnBlendingOut = MontageInstance->OnMontageBlendingOutStarted;
	OnBlendingOut.Unbind();
	OnBlendingOut.BindUObject(this, &UKnockDownAbility::OnMontageBlendingOut);
}

void UKnockDownAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	ASC->RemoveLooseGameplayTag(R1Tags::Ability_Action_HitReact_Getup);
}

void UKnockDownAbility::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	ASC->RemoveLooseGameplayTag(R1Tags::Ability_Action_HitReact_Knockdown);
	ASC->AddLooseGameplayTag(R1Tags::Ability_Action_HitReact_Getup);
}

