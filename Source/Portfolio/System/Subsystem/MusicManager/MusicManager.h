

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "MusicManager.generated.h"


class AMusicPlayback;


UCLASS()
class PORTFOLIO_API UMusicManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static UMusicManager* Get(const UObject* WorldContextObject);
	
public:
	void ResetPlaybacks(TArray<TObjectPtr<AMusicPlayback>> SettingPlaybacks, FGameplayTag StartMoodeTag);

protected:
	TArray<TObjectPtr<AMusicPlayback>> Playbacks;

};
