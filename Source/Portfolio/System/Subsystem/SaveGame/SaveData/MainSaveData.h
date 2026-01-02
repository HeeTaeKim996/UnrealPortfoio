

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveData.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UMainSaveData : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SaveDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TempString = TEXT("-");
};
