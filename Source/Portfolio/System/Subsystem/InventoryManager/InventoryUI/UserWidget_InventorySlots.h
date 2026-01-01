

	#pragma once

	#include "CoreMinimal.h"
	#include "UI/R1UserWidget.h"
	#include "UserWidget_InventorySlots.generated.h"


	class UUniformGridPanel;
	class UUserWidget_InventorySlot;
	class UUserWidget_InventoryEntry;
	class UR1ItemInstance;
	class UCanvasPanel;

	UCLASS()
	class PORTFOLIO_API UUserWidget_InventorySlots : public UR1UserWidget
	{
		GENERATED_BODY()
	public:
		UUserWidget_InventorySlots();

	protected:
		virtual void NativeConstruct() override;

		void OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UR1ItemInstance> Item);

	protected:
		UPROPERTY()
		TSubclassOf<UUserWidget_InventorySlot> SlotWidgetClass;

		UPROPERTY()
		TArray<TObjectPtr<UUserWidget_InventorySlot>> SlotWidgets;

		UPROPERTY()
		TSubclassOf<UUserWidget_InventoryEntry> EntryWidgetClass;

		UPROPERTY()
		TArray<TObjectPtr<UUserWidget_InventoryEntry>> EntryWidgets;

		UPROPERTY(meta = (BindWidget))
		TObjectPtr<UUniformGridPanel> GridPanel_Slots;

		UPROPERTY(meta = (BindWidget))
		TObjectPtr<UCanvasPanel> CanvasPanel_Entries;
	};
