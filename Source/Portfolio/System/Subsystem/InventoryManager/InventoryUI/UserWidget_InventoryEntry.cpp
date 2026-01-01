


#include "System/Subsystem/InventoryManager/InventoryUI/UserWidget_InventoryEntry.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UserWidget_InventorySlots.h"
#include "../Item/R1ItemInstance.h"
#include "../Item/ItemStructures/ItemDefines.h"
#include "../Item/Drag/R1DragDropOperation.h"
#include "UserWidget_ItemDrag.h"

UUserWidget_InventoryEntry::UUserWidget_InventoryEntry()
	: Super()
{
	ConstructorHelpers::FClassFinder<UUserWidget_ItemDrag> FindDragWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory/WBP_ItemDrag.WBP_ItemDrag_C'"));
	if (FindDragWidgetClass.Succeeded())
	{
		DrawWidgetClass = FindDragWidgetClass.Class;
	}
}

void UUserWidget_InventoryEntry::Init(UUserWidget_InventorySlots* InSlotsWidget, UR1ItemInstance* InItemInstance, int32 InItemCount)
{
	SlotsWidget = InSlotsWidget;
	ItemInstance = InItemInstance;
	ItemCount = InItemCount;
}

void UUserWidget_InventoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	TEXT_Count->SetText(FText::GetEmpty());
	Image_Hover->SetRenderOpacity(0.f);
}

void UUserWidget_InventoryEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Image_Hover->SetRenderOpacity(1.f);
}

void UUserWidget_InventoryEntry::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Image_Hover->SetRenderOpacity(0.f);
}

FReply UUserWidget_InventoryEntry::NativeOnMouseButtonDown(const FGeometry& InGeometry, 
	const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	const FIntPoint UnitInventorySlotSize = FIntPoint(ITEM_SLOT_WIDTH, ITEM_SLOT_HEIGHT);

	FVector2D MouseWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()); // Mouse's Local(Slots) Position
	FVector2D ItemWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UnitInventorySlotSize / 2.f)); 
	// Entry(Slot)'s CenterPos(UnitInventorySlotSize / 2.f)'s Local(Slots) Position
	FIntPoint ItemSlotPos = FIntPoint(ItemWidgetPos.X / UnitInventorySlotSize.X, ItemWidgetPos.Y / UnitInventorySlotSize.Y);
	// Entry(Slot)'s X, Y Index

	CachedFromSlotPos = ItemSlotPos;
	CachedDeltaWidgetPos = MouseWidgetPos - ItemWidgetPos;
	
	return Reply;	
}

void UUserWidget_InventoryEntry::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UUserWidget_ItemDrag* DragWidget = CreateWidget<UUserWidget_ItemDrag>(GetOwningPlayer(), DrawWidgetClass);
	FVector2D EnitytyWidgetSize = FVector2D(1 * ITEM_SLOT_WIDTH, 1 * ITEM_SLOT_HEIGHT);
	DragWidget->Init(EnitytyWidgetSize, nullptr, ItemCount);

	UR1DragDropOperation* DragDrop = NewObject<UR1DragDropOperation>();
	DragDrop->DefaultDragVisual = DragWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->FromItemSlotPos = CachedFromSlotPos;
	DragDrop->ItemInstance = ItemInstance;
	DragDrop->DeltaWidgetPos = CachedDeltaWidgetPos;
	//DragDrop->DeltaWidgetPos = FVector2D::Zero();

	OutOperation = DragDrop;
}

void UUserWidget_InventoryEntry::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

}

void UUserWidget_InventoryEntry::RefreshWidgetOpacity(bool bClearVisible)
{
	SetRenderOpacity(bClearVisible ? 1.f : 0.5f);
}

void UUserWidget_InventoryEntry::RefreshItemCount(int32 NewItemCount)
{
	ItemCount = NewItemCount;
	TEXT_Count->SetText(ItemCount >= 2 ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}
