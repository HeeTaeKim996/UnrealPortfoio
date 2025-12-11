

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASC/CharacterASC.h"
#include "System/R1GameplayTags.h"
#include "PlayerASC.generated.h"

struct FGameplayAbilitySpecHandle;

UCLASS()
class PORTFOLIO_API UPlayerASC : public UCharacterASC
{
	GENERATED_BODY()
public:
	UPlayerASC();

public:
	virtual FGameplayAbilitySpecHandle ActivateAbility(FGameplayTag InTag) override;

public:
	FGameplayAbilitySpecHandle ActivateAbilityByInputMap(FGameplayTag InStateTag);
	int GetComboCount() { return ComboCount; }
	

private:
	TMap<FGameplayTag, FGameplayTag> InputToAbilityMap;
	int ComboCount = 0;
};
