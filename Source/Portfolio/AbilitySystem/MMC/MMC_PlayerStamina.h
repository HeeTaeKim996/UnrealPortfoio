

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_PlayerStamina.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UMMC_PlayerStamina : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	static FGameplayTagContainer NoStaminaTags;
};
