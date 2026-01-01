


#include "System/Subsystem/InventoryManager/InventoryUI/UserWidget_ItemDrag.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

UUserWidget_ItemDrag::UUserWidget_ItemDrag()
	: Super() 
{

}

void UUserWidget_ItemDrag::Init(const FVector2D& InWidgetSize, UTexture2D* InItemIcon, int32 InItemCount)
{
	SizeBox_Root->SetWidthOverride(InWidgetSize.X);
	SizeBox_Root->SetHeightOverride(InWidgetSize.Y);

	Image_Icon->SetBrushFromTexture(InItemIcon);
	Text_Count->SetText(InItemCount >= 2 ? FText::AsNumber(InItemCount) : FText::GetEmpty());
}
