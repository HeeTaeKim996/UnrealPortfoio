

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "R1AbilitySystemComponent.generated.h"



/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AddCharacterAbilities(const TArray<TSubclassOf<class UR1GameplayAbility>>& StartupAbilities);

	void ActivateAbility(FGameplayTag InTag);

	void SetState(const FGameplayTag& RootTag, FGameplayTag NewState);


public:
	static const FGameplayTag LifeRootTag;
	static const FGameplayTag HitStateRootTag;
	static const FGameplayTag InputRootTag;

protected:
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
};
