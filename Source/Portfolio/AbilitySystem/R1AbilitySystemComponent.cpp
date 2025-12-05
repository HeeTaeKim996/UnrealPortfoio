


#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"


UR1AbilitySystemComponent::UR1AbilitySystemComponent()
	: Super()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(
		this,
		&UR1AbilitySystemComponent::OnGEApplied);
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

	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && Spec->Ability->AbilityTags.First().MatchesTag(COD->AbilityTags.First()))
				// Prelude First Tag Represents Ability
			{
				ensureAlwaysMsgf(!Spec->IsActive(), TEXT("ASC Already Has That ability"));

				return;
			}
		}
	}

	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AddAbility, 1);
	FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
	SpecHandles.Add(SpecHandle);
}

void UR1AbilitySystemComponent::RemoveAbilityByStateTag(FGameplayTag InStateTag)
{
	for(int i = SpecHandles.Num() - 1; i >= 0; i--)
	{
		FGameplayAbilitySpecHandle& SpecHandle = SpecHandles[i];
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (UCharacterAbility* CharacterAbility = Cast<UCharacterAbility>(Spec->Ability))
			{
				if (CharacterAbility->GetStateTag().MatchesTag(InStateTag))
				{
					SpecHandles.RemoveAt(i);
					ClearAbility(SpecHandle);
				}
			}
		}
	}
}

void UR1AbilitySystemComponent::RemoveAbilityByAbilityTag(FGameplayTag InAbilityTag)
{
	for (int i = SpecHandles.Num() - 1; i >= 0; i--)
	{
		FGameplayAbilitySpecHandle& SpecHandle = SpecHandles[i];
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && Spec->Ability->AbilityTags.HasTag(InAbilityTag))
			{
				SpecHandles.RemoveAt(i);
				ClearAbility(SpecHandle);
			}
		}
	}
}

void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag InTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && Spec->Ability->AbilityTags.HasTag(InTag))
			{
				if (Spec->IsActive())
				{
					UCharacterAbility* R1Ability = Cast<UCharacterAbility>(Spec->Ability);
					
					if (R1Ability && R1Ability->GetStateTag().MatchesTag(R1Tags::State_Action_HitReact))
					{
						R1Ability->CancelAbility(SpecHandle, R1Ability->GetCurrentActorInfo(),
							R1Ability->GetCurrentActivationInfo(), true);
					}
					else
					{
						ensureAlwaysMsgf(false, TEXT("Ability is Already Active"));
						return;
					}
				}

				TryActivateAbility(SpecHandle);
				return;
			}
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

void UR1AbilitySystemComponent::OnGEApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, 
	FActiveGameplayEffectHandle ActiveHandle)
{
	DebugMessage(TEXT("R1ASC : Check"));
}

