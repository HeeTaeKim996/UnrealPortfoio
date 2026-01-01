

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FieldMonsterManager.generated.h"

class AFieldMonster;

USTRUCT()
struct FStreamingMonsters
{
	GENERATED_BODY()

	TArray<TObjectPtr<AFieldMonster>> FieldMonsters;
};

USTRUCT()
struct FLevelSet
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<FName> Levels;
};


UCLASS()
class PORTFOLIO_API UFieldMonsterManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	static UFieldMonsterManager* Get(const UObject* WorldContextObject);

private:
	void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);
	void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);



public:
	void RegisterFieldMonster(const FName& LandLevelName, const FName& StreamingLevelName, 
		AFieldMonster* FieldMonster);
	void OnLeaveWork(const FName& StreamingLevelName, AFieldMonster* FieldMonster);



protected:
	UPROPERTY()
	TMap<FName, FStreamingMonsters> FMonstersMap;

	UPROPERTY()
	TMap<FName, FLevelSet> LandToStreamMap;

	TSet<FName> ActiveLevelNames;

private:
	FDelegateHandle DelegateHandle_LevelAddedToWorld;
	FDelegateHandle DelegateHandle_LevelRemovedFromWorld;
};
