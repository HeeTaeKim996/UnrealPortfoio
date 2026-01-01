


#include "GameMode/R1GameModeBase.h"
#include "System/Subsystem/InventoryManager/InventoryManager.h"

void AR1GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UInventoryManager* InventoryManager = UInventoryManager::Get(GetWorld());
	InventoryManager->AddDefaultItems();
}
