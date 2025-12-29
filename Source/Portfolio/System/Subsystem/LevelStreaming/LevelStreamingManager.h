

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelStreamingManager.generated.h"

class ALevelStreamingTrigger;

UCLASS()
class PORTFOLIO_API ULevelStreamingManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static ULevelStreamingManager* Get(const UObject* WorldContextObject);

public:
	void AddLevel(TSoftObjectPtr<UWorld> Level, ALevelStreamingTrigger* Trigger);
	void RemoveLevel(TSoftObjectPtr<UWorld> Level, ALevelStreamingTrigger* Trigger);

protected:
	TMap<TSoftObjectPtr<UWorld>, TArray<TObjectPtr<ALevelStreamingTrigger>>> StreamMap;
};
