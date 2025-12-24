


#include "System/Subsystem/MusicManager/MusicManager.h"


void UMusicManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

UMusicManager* UMusicManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UMusicManager>();
	}
	return nullptr;
}

void UMusicManager::ResetPlaybacks(TArray<TObjectPtr<AMusicPlayback>> SettingPlaybacks, FGameplayTag StartMoodeTag)
{
	
}