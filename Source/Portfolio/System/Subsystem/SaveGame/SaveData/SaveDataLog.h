

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../SaveStructures/SaveSlotMeta.h"
#include "SaveDataLog.generated.h"



UCLASS()
class PORTFOLIO_API USaveDataLog : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FSaveSlotMeta> Slots;
};
