


#include "System/Subsystem/FieldMonsterManager/FieldMonsterManager.h"
#include "R1Define.h"
#include "Character/FieldMonster.h"

void UFieldMonsterManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UFieldMonsterManager::OnLevelAdded);

	FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &UFieldMonsterManager::OnLevelRemoved);
}

void UFieldMonsterManager::Deinitialize()
{
	// TODO

	Super::Deinitialize();
}

UFieldMonsterManager* UFieldMonsterManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UFieldMonsterManager>();
	}
	return nullptr;
}









void UFieldMonsterManager::OnLevelAdded(ULevel* InLevel, UWorld* InWorld)
{
	if (InWorld == nullptr) return;

#if 0
	const FString PackageName =
		FString::Printf(TEXT("FieldMonsterManager.cpp : Add [%s]"), *InLevel->GetOutermost()->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, PackageName);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PackageName);
#endif


	const FName LevelName = InLevel->GetOutermost()->GetFName();

	ActiveLevelNames.Add(LevelName);

	if (FStreamingMonsters* StreamingMonsters = FMonstersMap.Find(LevelName))
	{
		for (AFieldMonster* FieldMonster : StreamingMonsters->FieldMonsters)
		{
			if (FieldMonster->IsSleeping() == true)
			{
				FieldMonster->Wakeup();
			}
		}
	}
}
void UFieldMonsterManager::OnLevelRemoved(ULevel* InLevel, UWorld* InWorld)
{
#if 0
	const FString PackageName =
		FString::Printf(TEXT("FieldMonsterManager.cpp : Removed [%s]"), *InLevel->GetOutermost()->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, PackageName);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PackageName);
#endif


	const FName LevelName = InLevel->GetOutermost()->GetFName();

	ActiveLevelNames.Remove(LevelName);

	if (FLevelSet* StreamingLevels = LandToStreamMap.Find(LevelName))
	{
		for (FName StreamingLevelName : StreamingLevels->Levels)
		{
			FMonstersMap.Remove(StreamingLevelName);
		}

		LandToStreamMap.Remove(LevelName);
	}
	else if (FStreamingMonsters* StreamingMonsters = FMonstersMap.Find(LevelName))
	{
		for (AFieldMonster* FieldMonster : StreamingMonsters->FieldMonsters)
		{
			if (FieldMonster->IsWorking() == false && FieldMonster->IsSleeping() == false)
			{
				FieldMonster->Sleep();
			}
		}
	}
}












void UFieldMonsterManager::RegisterFieldMonster(const FName& LandLevelName, const FName& StreamingLevelName,
	AFieldMonster* FieldMonster)
{
	if (StreamingLevelName.IsValid() == false || FieldMonster == nullptr) return;

	FStreamingMonsters& StreamingMonsters = FMonstersMap.FindOrAdd(StreamingLevelName);
	
	StreamingMonsters.FieldMonsters.Add(FieldMonster);


	FLevelSet& StreamingLevels = LandToStreamMap.FindOrAdd(LandLevelName);
	StreamingLevels.Levels.Add(StreamingLevelName);

	if(ActiveLevelNames.Contains(StreamingLevelName) == false)
	{
		FieldMonster->Sleep();
	}
}

void UFieldMonsterManager::OnLeaveWork(const FName& StreamingLevelName, AFieldMonster* FieldMonster)
{
	if (ActiveLevelNames.Contains(StreamingLevelName) == false)
	{
		FieldMonster->Sleep();
	}
}



