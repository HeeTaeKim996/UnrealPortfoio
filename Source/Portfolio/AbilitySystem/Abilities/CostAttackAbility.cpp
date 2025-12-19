


#include "AbilitySystem/Abilities/CostAttackAbility.h"

UCostAttackAbility::UCostAttackAbility()
	: Super()
{
}

bool UCostAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) 
	const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		if (CheckCost(Handle, ActorInfo, nullptr) == false)
		{
			DebugMessage(TEXT("CostAttackAbility.cpp : Coist is InSufficient"));
		}

		return false;
	}
	return true;
}

void UCostAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// ※ CommitAbility Invoke CommitCost + CommitCooldown. To Use it Separately, Use CommitABilityCost, CommitAbilityCooldown

	if (CommitAbilityCost(Handle, ActorInfo, ActivationInfo) == false) 
	{
		EndAbilityCancel();
		return;
	}
}
