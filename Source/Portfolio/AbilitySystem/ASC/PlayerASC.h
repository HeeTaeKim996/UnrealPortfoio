

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
	int GetComboCount() { return ComboCount; }
	

private:
	int ComboCount = 0;
};
