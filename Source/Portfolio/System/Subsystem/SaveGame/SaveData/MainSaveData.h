

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector PlayerPos = FVector::Zero();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator PlayerRot = FRotator::ZeroRotator;

};
