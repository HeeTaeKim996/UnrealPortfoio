

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicManager.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UMusicManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	static UMusicManager* Get(const UObject* WorldContextObject);
};
