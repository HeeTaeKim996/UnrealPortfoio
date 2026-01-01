

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "UserWidget_ItemDrag.generated.h"

class UTexture2D;
class USizeBox;
class UImage;
class UTextBlock;


UCLASS()
class PORTFOLIO_API UUserWidget_ItemDrag : public UR1UserWidget
{
	GENERATED_BODY()
	
public:
	UUserWidget_ItemDrag();

	void Init(const FVector2D& InWidgetSize, UTexture2D* InItemIcon, int32 InItemCount);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;


};