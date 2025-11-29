#pragma once
#include "GameplayTagContainer.h"
#include "AbilityCommonStruct.generated.h"

UENUM(BlueprintType)
enum class CancelCause
{
	ShutDown,
	Temp,
};

USTRUCT()
struct PORTFOLIO_API FAbilityCancelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	CancelCause Cause;
};

USTRUCT()
struct PORTFOLIO_API FAbilitySuccessInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag AbilityTag;

	UPROPERTY()
	uint8 Temp;
};
