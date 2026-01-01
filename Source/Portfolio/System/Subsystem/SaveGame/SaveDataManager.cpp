


#include "System/Subsystem/SaveGame/SaveDataManager.h"
#include "SaveData/MainSaveData.h"
#include "Kismet/GameplayStatics.h"

void USaveDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

USaveDataManager* USaveDataManager::Get(const UObject* WorldContext)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<USaveDataManager>();
	}
	
	return nullptr;
}

void USaveDataManager::TempSave()
{
	const FString SlotName = TEXT("TempSave");
	const int32 UserIndex = 0;

	UMainSaveData* SaveObject = Cast<UMainSaveData>(UGameplayStatics::CreateSaveGameObject
	(UMainSaveData::StaticClass()));

	SaveObject->SaveDateTime = FDateTime::Now().ToString(TEXT("%Y-%m-%d %H:%M:%S"));

	const FString Msg = FString::Printf(TEXT("SaveDataManager.cpp : SaveDate : [%s]"), *SaveObject->SaveDateTime);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, Msg);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, UserIndex);
}

UMainSaveData* USaveDataManager::TempLoad()
{
	const FString SlotName = TEXT("TempSave");
	const int32 UserIndex = 0;
	
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex) == false)
	{
		const FString Msg = FString::Printf(TEXT("SaveDataManager.cpp : NoDataToLoad"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, Msg);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

		return nullptr;
	}
		

	UMainSaveData* SaveData = Cast<UMainSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

	const FString Msg = FString::Printf(TEXT("SaveDataManager.cpp : LoadDate : [%s]"), *SaveData->SaveDateTime);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, Msg);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	return SaveData;
}
