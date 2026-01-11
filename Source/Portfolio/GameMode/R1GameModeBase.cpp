


#include "GameMode/R1GameModeBase.h"
#include "System/Subsystem/InventoryManager/InventoryManager.h"
#include "System/Subsystem/SaveGame/SaveDataManager.h"
#include "System/Subsystem/SaveGame/SaveData/MainSaveData.h"
#include "GameFramework/PlayerStart.h"
#include "System/MainGameStateBase.h"

void AR1GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UInventoryManager* InventoryManager = UInventoryManager::Get(GetWorld());
	InventoryManager->AddDefaultItems();



}

void AR1GameModeBase::InitGameState()
{
	Super::InitGameState();

	AMainGameStateBase* GS = GetGameState<AMainGameStateBase>();
	ensureAlwaysMsgf(GS, TEXT("GS is not MainGameStteBase"));

	GS->Initialize_SuqsGameStateComponent();
}

AActor* AR1GameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (bUsePlayerStartPos == true) return Super::ChoosePlayerStart_Implementation(Player);
	
	USaveDataManager* SaveDataManager = USaveDataManager::Get(this);
	if (SaveDataManager == nullptr) return Super::ChoosePlayerStart_Implementation(Player);

	if(SaveDataManager->GetCurrentData() == nullptr) return Super::ChoosePlayerStart_Implementation(Player);
	

	FVector StartPos = SaveDataManager->GetCurrentData()->PlayerPos;
	FRotator StartRot = SaveDataManager->GetCurrentData()->PlayerRot;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.ObjectFlags |= RF_Transient; // ¡Ø Objects is Runtime tempoary Object

	APlayerStart* TempStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), StartPos, StartRot,
		Params);

	return TempStart ? TempStart : Super::ChoosePlayerStart_Implementation(Player);
}
