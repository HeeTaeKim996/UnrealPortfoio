

#pragma once

#include "CoreMinimal.h"
#include "TraceHitInfo.generated.h"

UENUM()
enum class ETraceHitResult
{

	Hit,
	Block,
	Parry
};


USTRUCT()
struct PORTFOLIO_API FTraceHitInfo
{
	GENERATED_BODY()

	UPROPERTY()
	ETraceHitResult TraceHitResult;
};