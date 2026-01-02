


#include "System/Subsystem/InventoryManager/InventoryUI/UserWidget_InventorySlots.h"
#include "UserWidget_InventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "UserWidget_InventoryEntry.h"
#include "../InventoryManager.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "../Item/Drag/R1DragDropOperation.h"
#include "../Item/ItemStructures/ItemDefines.h"

#define SLOTS_X_COUNT 10
#define SLOTS_Y_COUNT 5

UUserWidget_InventorySlots::UUserWidget_InventorySlots()
	: Super()
{
	ConstructorHelpers::FClassFinder<UUserWidget_InventorySlot> FindSlotWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'"));
	if (FindSlotWidgetClass.Succeeded())
	{
		SlotWidgetClass = FindSlotWidgetClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget_InventoryEntry> FindEntryWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory/WBP_InventoryEntry.WBP_InventoryEntry_C'"));
	if (FindEntryWidgetClass.Succeeded())
	{
		EntryWidgetClass = FindEntryWidgetClass.Class;
	}

}

void UUserWidget_InventorySlots::NativeConstruct()
{
	Super::NativeConstruct();

	SlotWidgets.SetNum(SLOTS_X_COUNT * SLOTS_Y_COUNT);

	for (int y = 0; y < SLOTS_Y_COUNT; y++)
	{
		for (int x = 0; x < SLOTS_X_COUNT; x++)
		{
			int Index = y * SLOTS_X_COUNT + x;

			UUserWidget_InventorySlot* SlotWidget =
				CreateWidget<UUserWidget_InventorySlot>(GetOwningPlayer(), SlotWidgetClass);
			SlotWidgets[Index] = SlotWidget;
			GridPanel_Slots->AddChildToUniformGrid(SlotWidget, y, x);
		}
	}

	EntryWidgets.SetNum(SLOTS_X_COUNT * SLOTS_Y_COUNT);
	UInventoryManager* InventoryManager = UInventoryManager::Get(GetWorld());

	const TArray<TObjectPtr<UR1ItemInstance>>& Items = InventoryManager->GetItems();
	for (int32 i = 0; i < Items.Num(); i++)
	{
		const TObjectPtr<UR1ItemInstance>& Item = Items[i];
		FIntPoint ItemSlotPos = FIntPoint(i % SLOTS_X_COUNT, i / SLOTS_X_COUNT);

		OnInventoryEntryChanged(ItemSlotPos, Item);
	}
}

bool UUserWidget_InventorySlots::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UR1DragDropOperation* DragDrop = Cast<UR1DragDropOperation>(InOperation);
	check(DragDrop);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToSlotPos = FIntPoint(ToWidgetPos.X / ITEM_SLOT_WIDTH, ToWidgetPos.Y / ITEM_SLOT_HEIGHT);

	if (PrevDragOverSlotPos == ToSlotPos) return true;
	
	PrevDragOverSlotPos = ToSlotPos;


	return false;
}

void UUserWidget_InventorySlots::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	FinishDrag();
}

bool UUserWidget_InventorySlots::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	FinishDrag();

	UR1DragDropOperation* DragDrop = Cast<UR1DragDropOperation>(InOperation);
	check(DragDrop);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToItemSlotPos = FIntPoint(ToWidgetPos.X / ITEM_SLOT_WIDTH, ToWidgetPos.Y / ITEM_SLOT_HEIGHT);

	if (DragDrop->FromItemSlotPos != ToItemSlotPos)
	{
		// TODO : Switch Items. Not just Setting before nullptr

		OnInventoryEntryChanged(DragDrop->FromItemSlotPos, nullptr);
		OnInventoryEntryChanged(ToItemSlotPos, DragDrop->ItemInstance);
	}

	return false;
}

void UUserWidget_InventorySlots::OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UR1ItemInstance> Item)
{
	int32 SlotIndex = ItemSlotPos.Y * SLOTS_X_COUNT + ItemSlotPos.X;

	if (UUserWidget_InventoryEntry* EntryWidget = EntryWidgets[SlotIndex])
	{
		if (Item == nullptr)
		{
			CanvasPanel_Entries->RemoveChild(EntryWidget);
			EntryWidgets[SlotIndex] = nullptr;
		}
	}
	else
	{
		EntryWidget = CreateWidget<UUserWidget_InventoryEntry>(GetOwningPlayer(), EntryWidgetClass);
		EntryWidgets[SlotIndex] = EntryWidget;

		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel_Entries->AddChildToCanvas(EntryWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(ItemSlotPos.X * 50, ItemSlotPos.Y * 50));


		EntryWidget->Init(this, Item, 1);

	}
}

void UUserWidget_InventorySlots::FinishDrag()
{
	PrevDragOverSlotPos = FIntPoint(-1, -1);
}
