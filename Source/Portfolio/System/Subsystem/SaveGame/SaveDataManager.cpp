


#include "System/Subsystem/SaveGame/SaveDataManager.h"
#include "SaveData/MainSaveData.h"
#include "Kismet/GameplayStatics.h"
#include "SaveData/SaveDataLog.h"

#define SAVE_DATAS_MAX_COUNT 10

void USaveDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FString MainMainSlotName = MainSlotTemplate + TEXT("Main");
	
	
	if (UGameplayStatics::DoesSaveGameExist(MainMainSlotName, 0) == true)
	{
		CurrentMainData = Cast<UMainSaveData>(UGameplayStatics::LoadGameFromSlot(MainMainSlotName, 0));
	}
	else
	{
		CurrentMainData = Cast<UMainSaveData>(UGameplayStatics::CreateSaveGameObject(UMainSaveData::StaticClass()));
	}

	if (UGameplayStatics::DoesSaveGameExist(SaveDataLogName, 0) == true)
	{
		SaveDataLog = Cast<USaveDataLog>(UGameplayStatics::LoadGameFromSlot(SaveDataLogName, 0));
	}
	else
	{
		SaveDataLog = Cast<USaveDataLog>(UGameplayStatics::CreateSaveGameObject(USaveDataLog::StaticClass()));
	}
}

USaveDataManager* USaveDataManager::Get(const UObject* WorldContext)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<USaveDataManager>();
	}
	
	return nullptr;
}

void USaveDataManager::SaveCurrent()
{
	CurrentMainData->SaveDateTime = FDateTime::Now().ToString(TEXT("%Y-%m-%d__%H-%M-%S"));

	FString MainMainSlotName = MainSlotTemplate + TEXT("Main");
	ensureAlwaysMsgf(UGameplayStatics::SaveGameToSlot(CurrentMainData, MainMainSlotName, 0), TEXT("SaveFailed. Slot Name MUST NOT CONTAINS ':'"));
}

void USaveDataManager::SaveAppendary()
{
	SaveCurrent();

	UMainSaveData* CurrentClone = DuplicateObject<UMainSaveData>(CurrentMainData, GetTransientPackage());
	if (CurrentClone == nullptr) return;

	TArray<FSaveSlotMeta>& Slots = SaveDataLog->Slots;
	
	if(Slots.Num() >= SAVE_DATAS_MAX_COUNT)
	{
		int RemoveCount = Slots.Num() - SAVE_DATAS_MAX_COUNT + 1;
		for (int i = 0; i < RemoveCount; i++)
		{
			UGameplayStatics::DeleteGameInSlot(Slots[i].SlotName, 0);
		}

		SaveDataLog->Slots.RemoveAt(0, SaveDataLog->Slots.Num() - SAVE_DATAS_MAX_COUNT + 1);
	}

	FSaveSlotMeta SaveSlotMeta;
	SaveSlotMeta.SaveDateTime = FDateTime::Now().ToString(TEXT("%Y-%m-%d__%H-%M-%S"));
	SaveSlotMeta.SlotName = MainSlotTemplate + SaveSlotMeta.SaveDateTime;

	ensureAlwaysMsgf(UGameplayStatics::SaveGameToSlot(CurrentClone, SaveSlotMeta.SlotName, 0), TEXT("SaveFailed. Slot Name MUST NOT CONTAINS ':'"));

	Slots.Add(SaveSlotMeta);

	ensureAlwaysMsgf(UGameplayStatics::SaveGameToSlot(SaveDataLog, SaveDataLogName, 0), TEXT("SaveFailed. Slot Name MUST NOT CONTAINS ':'"));
}

void USaveDataManager::SwitchCurrentMainData(FString SlotName)
{
#if 0
	for (FSaveSlotMeta& Test : SaveDataLog->Slots)
	{
		if (Test.SlotName == SlotName)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("@@@@@@@@@@@@@@")));
		}
	}
#endif

	ensureAlwaysMsgf(UGameplayStatics::DoesSaveGameExist(SlotName, 0), TEXT("Can't Find Data"));

	UMainSaveData* SwitchingData = Cast<UMainSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	CurrentMainData = SwitchingData;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("SaveDataManager.cpp : [%s]"), *CurrentMainData->SaveDateTime));
}

TArray<FSaveSlotMeta>& USaveDataManager::GetSaveDatas()
{
	return SaveDataLog->Slots;
}
