

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "UserWidget_InventoryEntry.generated.h"

class USizeBox;
class UTextBlock;
class UImage;
class UUserWidget_InventorySlots;
class UR1ItemInstance;
class UUserWidget_ItemDrag;

UCLASS()
class PORTFOLIO_API UUserWidget_InventoryEntry : public UR1UserWidget
{
	GENERATED_BODY()
public:
	UUserWidget_InventoryEntry();

public:
	void Init(UUserWidget_InventorySlots* InSlotsWidget, UR1ItemInstance* InItemInstance, int32 InItemCount);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	void RefreshWidgetOpacity(bool bClearVisible);
	void RefreshItemCount(int32 NewItemCount);


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TEXT_Count;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Hover;

protected:
	UPROPERTY()
	TObjectPtr<UUserWidget_InventorySlots> SlotsWidget;

	UPROPERTY()
	TObjectPtr<UR1ItemInstance> ItemInstance;

	UPROPERTY()
	TSubclassOf<UUserWidget_ItemDrag> DrawWidgetClass;

private:
	FIntPoint CachedFromSlotPos = FIntPoint::ZeroValue; // FIntPoint :  Two Vector composed of int. not float
	FVector2D CachedDeltaWidgetPos = FVector2D::ZeroVector;
	int32 ItemCount = 0;


};
