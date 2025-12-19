


#include "AbilitySystem/Abilities/Action/HitReact/KnockDownAbility.h"
#include "Structures/FNameContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "Character/R1Character.h"

void UKncokDownAbilityTask::Activate()
{
	Super::Activate();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->Delegate_GAMultiDelegate.AddDynamic(this, &UKncokDownAbilityTask::OnDelegate_GAMultiDelegate);
	}
}

void UKncokDownAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UKncokDownAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->Delegate_GAMultiDelegate.RemoveDynamic(this, &UKncokDownAbilityTask::OnDelegate_GAMultiDelegate);
	}
}

void UKncokDownAbilityTask::OnDelegate_GAMultiDelegate(const FGameplayTag& InTag)
{
	if (InTag != R1Tags::Event_GAS_KnockdownGetup) return;

	Ability->GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(R1Tags::Ability_HitState_Invincible);
	Cast<UKnockDownAbility>(Ability)->OnGetup();
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

	bIsInvincible = true;
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(R1Tags::Ability_HitState_Invincible);

	UKncokDownAbilityTask* Task = UAbilityTask::NewAbilityTask<UKncokDownAbilityTask>(this);
	Task->ReadyForActivation();
}

void UKnockDownAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (bIsInvincible)
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(R1Tags::Ability_HitState_Invincible);
		bIsInvincible = false;
	}
}

void UKnockDownAbility::OnGetup()
{
	GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(R1Tags::Ability_HitState_Invincible);
	bIsInvincible = false;
}



