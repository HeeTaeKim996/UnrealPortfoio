

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
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health); 
	/*	- Making '~Def' && '~Property' Member Macro
		- ~Def : To Load Captured Data. ~Property : To Apply Revised Data */
	DECLARE_ATTRIBUTE_CAPTUREDEF(BaseDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Impacted);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Impact);
};
