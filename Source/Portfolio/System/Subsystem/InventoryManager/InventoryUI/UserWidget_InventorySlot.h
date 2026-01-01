

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "UserWidget_InventorySlot.generated.h"

class USizeBox;
class UImage;

UCLASS()
class PORTFOLIO_API UUserWidget_InventorySlot : public UR1UserWidget
{
	GENERATED_BODY()
public:
	UUserWidget_InventorySlot();

protected:
	virtual void NativeConstruct() override;

#if 0 // Obsolate
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
		UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;
#endif

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Slot;	

};
