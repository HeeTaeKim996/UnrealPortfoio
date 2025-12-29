


#include "System/Subsystem/LevelStreaming/LevelStreamingManager.h"
#include "LevelStreamingTrigger.h"
#include "Kismet/GameplayStatics.h"

void ULevelStreamingManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

ULevelStreamingManager* ULevelStreamingManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<ULevelStreamingManager>();
	}
	return nullptr;
}

void ULevelStreamingManager::AddLevel(TSoftObjectPtr<UWorld> Level, ALevelStreamingTrigger* Trigger)
{
	if (Level.IsNull() || Trigger == nullptr) return;

	
	TArray<TObjectPtr<ALevelStreamingTrigger>>& Triggers = StreamMap.FindOrAdd(Level);

	if (Triggers.Contains(Trigger)) return;

	Triggers.Add(Trigger);

	if (Triggers.Num() == 1)
	{
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), Level, true, false, FLatentActionInfo());
	}
}

void ULevelStreamingManager::RemoveLevel(TSoftObjectPtr<UWorld> Level, ALevelStreamingTrigger* Trigger)
{
	if (Level.IsNull() || Trigger == nullptr) return;

	TArray<TObjectPtr<ALevelStreamingTrigger>>* Triggers = StreamMap.Find(Level);
	if (Triggers == nullptr) return;

	Triggers->Remove(Trigger);

	if (Triggers->Num() == 0)
	{
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), Level, FLatentActionInfo(), false);
		StreamMap.Remove(Level);
	}
}
