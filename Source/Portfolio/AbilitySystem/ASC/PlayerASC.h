

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASC/CharacterASC.h"
#include "System/R1GameplayTags.h"
#include "PlayerASC.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPlayerASC : public UCharacterASC
{
	GENERATED_BODY()
public:
	UPlayerASC();
public:
	void Action(FGameplayTag InStateTag);

protected:
	TMap<FGameplayTag, FGameplayTag> InputToAbilityMap;
};
