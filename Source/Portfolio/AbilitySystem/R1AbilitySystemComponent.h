

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

protected:
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
};
