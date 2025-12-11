

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "R1AbilitySystemComponent.generated.h"

class UR1GameplayAbility;

DECLARE_DELEGATE_TwoParams(FOnTagUpdated,
	const FGameplayTag&, bool)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNotifyAbilityEnded,
	FGameplayAbilitySpecHandle, Handle, UGameplayAbility*, Ability, bool, bWasCancelled);


UCLASS()
class PORTFOLIO_API UR1AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UR1AbilitySystemComponent();
	
public:
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;
	
	virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability,
		bool bWasCancelled) override;

public:
	void AddCharacterAbilities(TArray<TSubclassOf<UR1GameplayAbility>>& StartupAbilities);
	void AddCharacterAbility(TSubclassOf<UR1GameplayAbility>& AddAbility);
	
	void RemoveAbilityByTag(FGameplayTag InStateTag);

	virtual FGameplayAbilitySpecHandle ActivateAbility(FGameplayTag InTag);
	void CancelAbilityByTag(FGameplayTag InTag);

	void PrintOwnedTags();

public:
	FOnTagUpdated Delegate_OnTagUpdated;
	FOnNotifyAbilityEnded Delegate_OnNotifyAbilityEnded;
};
