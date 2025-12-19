

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASC/CharacterASC.h"
#include "System/R1GameplayTags.h"
#include "PlayerASC.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayEffect;

UCLASS()
class PORTFOLIO_API UPlayerASC : public UCharacterASC
{
	GENERATED_BODY()
public:
	UPlayerASC();
public:
	virtual void BeginPlay() override;

public:
	virtual FGameplayAbilitySpecHandle ActivateAbility(FGameplayTag InTag) override;

public:
	int GetComboCount() { return ComboCount; }
	void SetLastComboTime(double SetTime) { LastComboTime = SetTime; }
	void ApplyNotPlayerStaminable();

private:
	int ComboCount = 0;
	double LastComboTime;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> GE_PlayerStamina;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> GE_NoPlayerStaminable;
};
