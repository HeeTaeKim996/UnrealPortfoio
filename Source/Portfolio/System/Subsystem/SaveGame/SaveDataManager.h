

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveDataManager.generated.h"

class UMainSaveData;

UCLASS()
class PORTFOLIO_API USaveDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static USaveDataManager* Get(const UObject* World);


	void TempSave();
	UMainSaveData* TempLoad();

};