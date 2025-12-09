


#include "AbilitySystem/Abilities/Action/HitReact/KnockDownAbility.h"
#include "Structures/FNameContainer.h"
#include "AbilitySystemBlueprintLibrary.h"

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
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_HitReact_Knockdown);

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

}

void UKnockDownAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UKnockDownAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	Super::OnMontageEnded(Montage, bInterruped);

	if (bInterruped == false)
	{
		EndAbilitySuccess();


		UFNameContainer* FNameContainer = NewObject<UFNameContainer>();
		FString Tmp = InSectionName.ToString() + TEXT("_Getup");
		FNameContainer->Name = FName(*Tmp);
		FGameplayEventData EventData;
		EventData.OptionalObject = FNameContainer;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),
			R1Tags::Ability_Action_HitReact_Getup, EventData);
	}
}
