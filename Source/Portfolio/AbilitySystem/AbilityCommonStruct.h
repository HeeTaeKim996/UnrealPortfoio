#pragma once
#include "GameplayTagContainer.h"
#include "AbilityCommonStruct.generated.h"

UENUM(BlueprintType)
enum class CancelCause
{
	ShutDownAll,
	OnActionInvoked,
};

USTRUCT()
struct PORTFOLIO_API FAbilityCancelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	CancelCause Cause;


	UPROPERTY()
	FGameplayTagContainer CancelTags;
};

