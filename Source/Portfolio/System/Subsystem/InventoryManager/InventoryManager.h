

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventoryManager.generated.h"

class UR1ItemInstance;

UCLASS()
class PORTFOLIO_API UInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static UInventoryManager* Get(const UObject* WorldContextObject);

	const TArray<TObjectPtr<UR1ItemInstance>>& GetItems() { return Items; }

public:
	void AddDefaultItems(); // TEMP

protected:
	UPROPERTY()
	TArray<TObjectPtr<UR1ItemInstance>> Items;
};

