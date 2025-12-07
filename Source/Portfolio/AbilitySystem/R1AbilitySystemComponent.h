

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "R1AbilitySystemComponent.generated.h"

class UR1GameplayAbility;

DECLARE_DELEGATE_TwoParams(FOnTagUpdated,
	const FGameplayTag&, bool)

UCLASS()
class PORTFOLIO_API UR1AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UR1AbilitySystemComponent();
	
public:
	void AddCharacterAbilities(TArray<TSubclassOf<UR1GameplayAbility>>& StartupAbilities);
	void AddCharacterAbility(TSubclassOf<UR1GameplayAbility>& AddAbility);
	
	void RemoveAbilityByTag(FGameplayTag InStateTag);



	bool ActivateAbility(FGameplayTag InTag);
	
	void ClearRoot(const FGameplayTag& RootTag);

	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;
	

public:
	FOnTagUpdated Delegate_OnTagUpdated;
};
