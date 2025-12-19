


#include "AbilitySystem/MMC/MMC_PlayerStamina.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "System/Subsystem/TagContainersManager.h"
#include "System/R1GameplayTags.h"


FGameplayTagContainer UMMC_PlayerStamina::NoStaminaTags;

float UMMC_PlayerStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	if (NoStaminaTags.IsEmpty())
	{
		NoStaminaTags.AddTagFast(R1Tags::Ability_Action);
		NoStaminaTags.AddTagFast(R1Tags::Ability_ETC_NoStaminaRegen);
		NoStaminaTags.AddTagFast(R1Tags::Ability_Dead);
	}

	UAbilitySystemComponent* ASC = Spec.GetEffectContext().GetInstigatorAbilitySystemComponent();

#if 0
	if (UR1AbilitySystemComponent* R1ASC = Cast<UR1AbilitySystemComponent>(ASC))
	{
		R1ASC->PrintOwnedTags();
	}
#endif

	if (ASC == nullptr) return 0;

	if (ASC->HasAnyMatchingGameplayTags(NoStaminaTags)) return 0;

	if (ASC->HasMatchingGameplayTag(R1Tags::Ability_Mode_Sprint))
	{
		return -0.08;
	}
	else
	{
		float BaseRegen = Spec.GetSetByCallerMagnitude(R1Tags::Data_SetByCaller_StaminaRegen, false, 0.f);
		if (ASC->HasMatchingGameplayTag(R1Tags::Ability_Mode_Blocking))
		{
			return BaseRegen * 0.4f;
		}
		else
		{
			return BaseRegen;
		}
	}
}
