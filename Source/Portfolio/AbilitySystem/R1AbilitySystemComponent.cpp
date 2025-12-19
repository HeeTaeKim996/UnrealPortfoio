


#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"


UR1AbilitySystemComponent::UR1AbilitySystemComponent()
	: Super()
{
}




void UR1AbilitySystemComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);
	Delegate_OnTagUpdated.Execute(Tag, TagExists);
}

void UR1AbilitySystemComponent::NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, 
	bool bWasCancelled)
{
	Super::NotifyAbilityEnded(Handle, Ability, bWasCancelled);

	Delegate_OnNotifyAbilityEnded.Broadcast(Handle, Ability, bWasCancelled);
}








void UR1AbilitySystemComponent::AddCharacterAbilities(
	TArray<TSubclassOf<class UR1GameplayAbility>>& StartupAbilities)
{
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



FGameplayAbilitySpecHandle UR1AbilitySystemComponent::ActivateAbility(FGameplayTag InTag)
{
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->AbilityTags.HasTag(InTag))
		{
			if (Spec.IsActive())
			{
				ensureAlwaysMsgf(false, TEXT("Ability is already active"));
				return FGameplayAbilitySpecHandle(); // return InvalidHandle
			}

			if (TryActivateAbility(Spec.Handle) == true)
			{
				return Spec.Handle;
			}
			else
			{
				return FGameplayAbilitySpecHandle();
			}
		}
	}

	return FGameplayAbilitySpecHandle();
}

void UR1AbilitySystemComponent::CancelAbilityByTag(FGameplayTag InTag)
{
	ABILITYLIST_SCOPE_LOCK();

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.IsActive() == false || Spec.Ability == nullptr) continue;

		if (Spec.Ability->AbilityTags.HasTag(InTag))
		{
			CancelAbilitySpec(Spec, nullptr);
		}
	}
}

void UR1AbilitySystemComponent::PrintOwnedTags()
{
	FGameplayTagContainer Container;
	GetOwnedGameplayTags(Container);
	DebugMessage("----------");
	for (const FGameplayTag& Tag : Container)
	{
		DebugMessage(FString::Printf(TEXT("[%s]"), *Tag.ToString()));
	}
}


