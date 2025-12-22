

#pragma once

#include "CoreMinimal.h"
#include "TriggerInfo.generated.h"

USTRUCT()
struct FTriggerInfo
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* TriggeringActor;
	AActor* TriggerOwner;
};
