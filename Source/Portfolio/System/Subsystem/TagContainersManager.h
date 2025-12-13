

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Data/DataAsset_GameplayTagContainers.h"
#include "TagContainersManager.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIO_API UTagContainersManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static UTagContainersManager* Get(const UObject* WorldContextObject);

public:
	const FGameplayTagContainer& BaseAbilityBlockTgs() const { return TagContainersData->BaseAbilityBlockTgs; }
	FORCEINLINE const FGameplayTagContainer& OnActionCall_BaseCancelingTags() const
	{
		return TagContainersData->OnActionCall_BaseCancelingTags;
	}

	FORCEINLINE const FGameplayTagContainer& OnHitReact_CancelTags() const
	{
		return TagContainersData->OnHitReact_CancelTags;
	}

	FORCEINLINE const FGameplayTagContainer& PlayerNotRegenableTags() const
	{
		return TagContainersData->PlayerNotRegenableTags;
	}

protected:
	UPROPERTY()
	TObjectPtr<UDataAsset_GameplayTagContainers> TagContainersData;
};
