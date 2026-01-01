

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStructures/ItemRarity.h"
#include "R1ItemInstance.generated.h"


UCLASS(BlueprintType)
class PORTFOLIO_API UR1ItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UR1ItemInstance();

public:
	void Init(int InItemID);

public:
	UPROPERTY()
	int ItemID = 0;

	UPROPERTY()
	EItemRarity ItemRarity = EItemRarity::Junk;
};
