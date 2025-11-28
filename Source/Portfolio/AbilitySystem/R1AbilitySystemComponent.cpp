


#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"


const FGameplayTag UR1AbilitySystemComponent::LifeRootTag = FGameplayTag::RequestGameplayTag(TEXT("State.Life"));
const FGameplayTag UR1AbilitySystemComponent::HitStateRootTag = FGameplayTag::RequestGameplayTag(TEXT("State.HitState"));
const FGameplayTag UR1AbilitySystemComponent::InputRootTag = FGameplayTag::RequestGameplayTag(TEXT("State.Input"));

void UR1AbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<class UR1GameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UR1GameplayAbility>& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
		// GiveAbility -> ActivatableAbilities.Add (New )
		SpecHandles.Add(SpecHandle);
	}

#if 0
	{
		for (const FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
		{
			if (Spec.Ability)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan,
					FString::Printf(TEXT("Ability : [%s], Level : [%d]."), *Spec.Ability.GetName(), Spec.Level));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Ability : Null"));
			}
		}
	}
#endif
}

void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag InTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && Spec->Ability->AbilityTags.HasTag(InTag))
			{
				ensureAlwaysMsgf(!Spec->IsActive(), TEXT("Ability is Already Active"));

				TryActivateAbility(SpecHandle);
				return;
			}
		}
	}
}

void UR1AbilitySystemComponent::SetState(const FGameplayTag& RootTag, FGameplayTag NewState)
{
	FGameplayTagContainer OwnedTags;
	GetOwnedGameplayTags(OwnedTags);

	for (const FGameplayTag& Tag : OwnedTags)
	{
		if (Tag.MatchesTag(RootTag))
		{
			RemoveLooseGameplayTag(Tag);
		}
	}

	AddLooseGameplayTag(NewState);
}

