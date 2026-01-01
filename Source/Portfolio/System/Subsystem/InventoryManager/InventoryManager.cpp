


#include "System/Subsystem/InventoryManager/InventoryManager.h"
#include "Item/R1ItemInstance.h"

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

UInventoryManager* UInventoryManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UInventoryManager>();
	}
	return nullptr;
}


void UInventoryManager::AddDefaultItems()
{
	UR1ItemInstance* Item = NewObject<UR1ItemInstance>();
	Item->Init(100);

	Items.Add(Item);
}
