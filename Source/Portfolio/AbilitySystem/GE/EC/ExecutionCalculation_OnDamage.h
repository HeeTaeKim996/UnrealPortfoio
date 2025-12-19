

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecutionCalculation_OnDamage.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UExecutionCalculation_OnDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecutionCalculation_OnDamage();
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	/*	- Making '~Def' && '~Property' Member Macro
		- ~Def : To Load Captured Data. ~Property : To Apply Revised Data */
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);

	DECLARE_ATTRIBUTE_CAPTUREDEF(MetaDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MetaImpact);
};
