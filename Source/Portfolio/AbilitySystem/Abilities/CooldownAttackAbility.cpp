


#include "AbilitySystem/Abilities/CooldownAttackAbility.h"


bool UCooldownAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		if (CheckCooldown(Handle, ActorInfo, nullptr) == false)
		{
			DebugMessage(TEXT("CooldownAttackAbility.cpp : Need More Time"));
		}

		return false;
	}
	return true;
}

void UCooldownAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false, nullptr) == false)
	{
		EndAbilityCancel();
		return;
	}
}

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
