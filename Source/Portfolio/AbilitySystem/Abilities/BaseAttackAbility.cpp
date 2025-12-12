


#include "AbilitySystem/Abilities/BaseAttackAbility.h"
#include "Character/R1Player.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "Structures/TraceHitInfo.h"

void UBaseAttackAbilityTask::Activate()
{
	Super::Activate();

	AR1Player* R1Player = Cast<AR1Player>(GetAvatarActor());
	if (R1Player == nullptr) return;

	R1Player->Delegate_OnBaseAttackOn.BindUObject(this, &UBaseAttackAbilityTask::OnPlayerBaseAttackOn);
	R1Player->SetGAState(EGAState::BaseAttackCancellable);
}

void UBaseAttackAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

}

void UBaseAttackAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	AR1Player* R1Player = Cast<AR1Player>(GetAvatarActor());
	if (R1Player == nullptr) return;
	R1Player->Delegate_OnBaseAttackOn.Unbind();
}

bool UBaseAttackAbilityTask::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Super::AttackSucceed(MeleeHitInfo, TraceHitInfo) == false) return false;

	return true;
}

void UBaseAttackAbilityTask::OnPlayerBaseAttackOn(FGameplayTag InAbilityTag)
{
	if (Ability->AbilityTags.HasTagExact(InAbilityTag))
	{
		AR1Player* R1Player = Cast<AR1Player>(GetAvatarActor());
		if (R1Player == nullptr) return;

		R1Player->SetGAState(EGAState::None);
	}
}


















UBaseAttackAbility::UBaseAttackAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_Attack_BaseAttack);
}

bool UBaseAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UBaseAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UPlayerASC* PlayerASC = Cast<UPlayerASC>(ActorInfo->AbilitySystemComponent);
	ensureAlwaysMsgf(PlayerASC, TEXT("BaseAttackAbility Must be used by PlayerASC"));

	ComboIndex = (PlayerASC->GetComboCount() - 1) % MaxComboCount;
	InSectionName = FName(*FString::FromInt(ComboIndex));

#if 1
	{
		FString Temp = FString::FromInt(ComboIndex);
		DebugMessage(FString::Printf(TEXT("BaseAttackABility.cpp : [%s]"), *Temp));
	}
#endif

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UBaseAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UPlayerASC* PlayerASC = Cast<UPlayerASC>(ActorInfo->AbilitySystemComponent);
	if (PlayerASC)
	{
		PlayerASC->SetLastComboTime(GetWorld()->TimeSeconds);
	}
		
}

