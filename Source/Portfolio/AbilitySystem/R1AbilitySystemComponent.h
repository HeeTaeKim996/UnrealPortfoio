

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "R1AbilitySystemComponent.generated.h"

class UR1GameplayAbility;

UCLASS()
class PORTFOLIO_API UR1AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AddCharacterAbilities(const TArray<TSubclassOf<UR1GameplayAbility>>& StartupAbilities);

	void ActivateAbility(FGameplayTag InTag);

	
	void ClearRoot(const FGameplayTag& RootTag);

	
protected:
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
};
