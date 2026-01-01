

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "R1DragDropOperation.generated.h"

class UR1ItemInstance;

UCLASS()
class PORTFOLIO_API UR1DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UR1DragDropOperation();
	
public:
	FIntPoint FromItemSlotPos = FIntPoint::ZeroValue;
	FVector2D DeltaWidgetPos = FVector2D::ZeroVector;
	
public:
	UPROPERTY()
	TObjectPtr<UR1ItemInstance> ItemInstance;
};
