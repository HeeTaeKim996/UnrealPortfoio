


#include "System/Subsystem/InventoryManager/InventoryUI/UserWidget_InventorySlot.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

UUserWidget_InventorySlot::UUserWidget_InventorySlot()
	: Super()
{

}

void UUserWidget_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Root->SetWidthOverride(50);
	SizeBox_Root->SetHeightOverride(50);

}

#if 0 // Obsolate
void UUserWidget_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UUserWidget_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UUserWidget_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton); // Invoke NativeOnDragDetected
	}

	return Reply;
}

void UUserWidget_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UUserWidget_InventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	 
}
#endif