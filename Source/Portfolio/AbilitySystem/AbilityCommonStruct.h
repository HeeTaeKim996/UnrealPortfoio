#pragma once
#include "GameplayTagContainer.h"
#include "AbilityCommonStruct.generated.h"

UENUM(BlueprintType)
enum class CancelCause
{
	ShutDownAll,
	OnActionInvoked,
	CancelMode
};

USTRUCT()
struct PORTFOLIO_API FAbilityCancelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	CancelCause Cause;

	UPROPERTY()
	FGameplayTagContainer StateCancelTags;


	UPROPERTY()
	FGameplayTagContainer AbilityCancelTags;
};

USTRUCT()
struct PORTFOLIO_API FAbilitySucceedInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGameplayTag StateSucceedTag;

	UPROPERTY()
	FGameplayTagContainer AbilitySucceedTags;
};