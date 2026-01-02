

#pragma once

#include "SaveSlotMeta.generated.h"

USTRUCT()
struct FSaveSlotMeta
{
	GENERATED_BODY()

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	FString SaveDateTime;
};
