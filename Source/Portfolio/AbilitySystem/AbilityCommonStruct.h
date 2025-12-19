#pragma once
#include "GameplayTagContainer.h"
#include "AbilityCommonStruct.generated.h"

UENUM(BlueprintType)
enum class CancelCause
{
	ShutDownAll,
	OnActionInvoked,
	CancelMode,
	HitReact,
};

USTRUCT()
struct PORTFOLIO_API FAbilityCancelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	CancelCause Cause;

	UPROPERTY()
	FGameplayTagContainer AbilityCancelTags;
};

USTRUCT()
struct PORTFOLIO_API FAbilitySucceedInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGameplayTagContainer AbilitySucceedTags;
};