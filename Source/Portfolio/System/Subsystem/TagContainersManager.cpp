


#include "System/Subsystem/TagContainersManager.h"

void UTagContainersManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// ※ Subsystem's Initialize is Eariler than GameInstance->Init ( invoke R1AssetManager's Init) 
	TagContainersData = LoadObject<UDataAsset_GameplayTagContainers>(nullptr,
		TEXT("/Script/Portfolio.DataAsset_GameplayTagContainers'/Game/Data/StaticPaths/DA_GameplayTagContainers.DA_GameplayTagContainers'"));
}



UTagContainersManager* UTagContainersManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UTagContainersManager>();
	}

	return nullptr;
}
