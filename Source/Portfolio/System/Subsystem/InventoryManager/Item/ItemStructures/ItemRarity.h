

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Junk,
	Poor,
	Common,
	Rare,
	Epic,
	Legendary,
	Unique,

	Count	UMETA(Hidden)
};