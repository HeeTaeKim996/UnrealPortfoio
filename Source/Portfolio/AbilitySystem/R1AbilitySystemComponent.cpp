


#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"


UR1AbilitySystemComponent::UR1AbilitySystemComponent()
	: Super()
{

}

void UR1AbilitySystemComponent::AddCharacterAbilities(
	TArray<TSubclassOf<class UR1GameplayAbility>>& StartupAbilities)
{
	ABILITYLIST_SCOPE_LOCK();

	for (TSubclassOf<UR1GameplayAbility>& AbilityClass : StartupAbilities)
	{
		AddCharacterAbility(AbilityClass);
	}
}

void UR1AbilitySystemComponent::AddCharacterAbility(TSubclassOf<UR1GameplayAbility>& AddAbility)
{
	UR1GameplayAbility* COD = AddAbility->GetDefaultObject<UR1GameplayAbility>();
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->AbilityTags.First().MatchesTag(COD->AbilityTags.First()))
			// Prelude First Tag Represents Ability
		{
			ensureAlwaysMsgf(false, TEXT("ASC Alreday Has that ability"));
			return;
		}
	}

	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AddAbility, 1);
	GiveAbility(AbilitySpec);
}

void UR1AbilitySystemComponent::RemoveAbilityByTag(FGameplayTag InTag)
{
	TArray<FGameplayAbilitySpecHandle> RemoveList;
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->AbilityTags.HasTag(InTag))
		{
			RemoveList.Add(Spec.Handle);
		}
	}

	for (FGameplayAbilitySpecHandle& SpecHandle : RemoveList)
	{
		ClearAbility(SpecHandle);
	}
}



void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag InTag)
{
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->AbilityTags.HasTag(InTag))
		{
			if (Spec.IsActive())
			{
				UCharacterAbility* R1Ability = Cast<UCharacterAbility>(Spec.Ability);
				if (R1Ability && R1Ability->GetStateTag().MatchesTag(R1Tags::State_Action_HitReact))
				{
					R1Ability->CancelAbility(Spec.Handle, R1Ability->GetCurrentActorInfo(),
						R1Ability->GetCurrentActivationInfo(), true);
				}
				else
				{
					ensureAlwaysMsgf(false, TEXT("Ability is already active"));
					return;
				}
			}

			TryActivateAbility(Spec.Handle);
			return;
		}
	}
}


void UR1AbilitySystemComponent::ClearRoot(const FGameplayTag& RootTag)
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
}


void UR1AbilitySystemComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);
	Delegate_OnTagUpdated.Execute(Tag, TagExists);
}


