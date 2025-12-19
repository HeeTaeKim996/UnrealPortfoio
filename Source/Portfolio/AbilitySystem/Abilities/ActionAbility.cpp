


#include "AbilitySystem/Abilities/ActionAbility.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "Character/R1Player.h"


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
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_MotionState_None);
}

void UActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AR1Player* R1Player = Cast<AR1Player>(ActorInfo->AvatarActor))
	{
		R1Player->SetGAState(EGAState::None);
	}
}

void UActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	
	if (AR1Player* R1Player = Cast<AR1Player>(ActorInfo->AvatarActor))
	{
		if (UPlayerASC* PlayerASC = Cast<UPlayerASC>(ActorInfo->AbilitySystemComponent))
		{
			PlayerASC->ApplyNotPlayerStaminable();
		}
	}
}



void UActionAbility::OnMontageBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted)
{
	Super::OnMontageBlendingOutStarted(AnimMontage, bInterrupted);

	if (AR1Player* R1Player = Cast<AR1Player>(GetAvatarActorFromActorInfo()))
	{
		R1Player->SetGAState(EGAState::ActionContinuable);
	}
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
