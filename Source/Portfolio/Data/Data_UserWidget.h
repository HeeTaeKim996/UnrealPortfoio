

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UData_UserWidget : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainUserWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UMenuUserWidget> MenuUserWidgetClass;

};
