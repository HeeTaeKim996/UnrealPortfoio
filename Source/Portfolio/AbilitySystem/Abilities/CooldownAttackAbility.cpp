


#include "AbilitySystem/Abilities/CooldownAttackAbility.h"


const FGameplayTagContainer* UCooldownAttackAbility::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);

	MutableTags->Reset();

	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}

	MutableTags->AppendTags(CooldownTags);

	return MutableTags;
}

void UCooldownAttackAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE == nullptr) return;

	FGameplayEffectSpecHandle SpecHandle 
		= MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
	if (SpecHandle.IsValid() == false) return;

	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();

	Spec->DynamicGrantedTags.AppendTags(CooldownTags);

	const float Duration = CooldownDuration.GetValueAtLevel(GetAbilityLevel());
	Spec->SetSetByCallerMagnitude(R1Tags::Data_SetByCaller_Cooldown, Duration);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
}
