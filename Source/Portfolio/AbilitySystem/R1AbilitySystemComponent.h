

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
	void AddCharacterAbilities(const TArray<TSubclassOf<UR1GameplayAbility>>& StartupAbilities);

	void ActivateAbility(FGameplayTag InTag);

	
	void ClearRoot(const FGameplayTag& RootTag);

	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;
	

public:
	FOnTagUpdated Delegate_OnTagUpdated;


protected:
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
};
