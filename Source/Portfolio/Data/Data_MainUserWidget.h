

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data_MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UData_MainUserWidget : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainUserWidget;

};
