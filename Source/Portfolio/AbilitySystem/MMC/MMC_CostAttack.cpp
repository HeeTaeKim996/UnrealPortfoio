


#include "AbilitySystem/MMC/MMC_CostAttack.h"
#include "AbilitySystem/Abilities/CostAttackAbility.h"

float UMMC_CostAttack::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UCostAttackAbility* Ability = Cast<UCostAttackAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (Ability == nullptr)
	{
		return 0.f;
	}

	float StaminaCost = Ability->StaminaCost.GetValueAtLevel(Ability->GetAbilityLevel());

	//DebugMessage(FString::Printf(TEXT("MMC_CostAttack : [%f]"), StaminaCost));

	return StaminaCost;
}	
