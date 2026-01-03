

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveDataManager.generated.h"

class UMainSaveData;
struct FSaveSlotMeta;
class USaveDataLog;

UCLASS()
class PORTFOLIO_API USaveDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static USaveDataManager* Get(const UObject* World);

public:
	void SaveCurrent();
	void SaveAppendary();
	void SwitchCurrentMainData(FString SlotName);
	TArray<FSaveSlotMeta>& GetSaveDatas();
	UMainSaveData* GetCurrentData();

private:
	UPROPERTY()
	TObjectPtr<UMainSaveData> CurrentMainData;

	UPROPERTY()
	TObjectPtr<USaveDataLog> SaveDataLog;

private:
	FString MainSlotTemplate = TEXT("Main_");
	FString SaveDataLogName = TEXT("SaveDataLog");
};