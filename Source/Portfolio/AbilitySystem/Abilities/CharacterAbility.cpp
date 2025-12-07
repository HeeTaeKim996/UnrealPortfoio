


#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "Character/R1Character.h"
#include "AbilitySystem/ASC/CharacterASC.h"


void UCharacterAbilityTask::Activate()
{
	Super::Activate();
	AbilityTag = Ability->AbilityTags.First();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->GAS_OnAbilityCancel.AddDynamic(this, &UCharacterAbilityTask::OnAbilityCancel);
	}
}

void UCharacterAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UCharacterAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);


	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->GAS_OnAbilityCancel.RemoveDynamic(this, &UCharacterAbilityTask::OnAbilityCancel);
	}
}



void UCharacterAbilityTask::OnAbilityCancel(FAbilityCancelInfo CancelInfo)
{
	AbilityCancel(MoveTemp(CancelInfo));
}

bool UCharacterAbilityTask::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	if (CancelInfo.Cause == CancelCause::ShutDownAll)
	{
		CancelAbility();
		return false;
	}
	
	
	for (const FGameplayTag& Tag : CancelInfo.AbilityCancelTags)
	{
		if (Ability->AbilityTags.HasTag(Tag))
		{
			CancelAbility();
			return true;
		}
	}

	return false;
}

UCharacterAbility::UCharacterAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCharacterAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UCharacterAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UCharacterAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (bWasCancelled == false)
	{
		AR1Character* R1Character = Cast<AR1Character>(ActorInfo->AvatarActor);
		if (R1Character)
		{
			FAbilitySucceedInfo SuccessInfo;			
			SuccessInfo.AbilitySucceedTags = AbilityTags;
			R1Character->Invoke_AbilitySucceed(SuccessInfo);
		}
	}
}
