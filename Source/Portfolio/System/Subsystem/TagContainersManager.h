

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
	const FGameplayTagContainer& CantBaseActableTags() const { return TagContainersData->CantBaseActableTags; }
	FORCEINLINE const FGameplayTagContainer& OnActionCall_CancelingTags() const
	{
		return TagContainersData->OnActionCall_CancelingTags;
	}

	FORCEINLINE const FGameplayTagContainer& OnHitReact_CancelTags() const
	{
		return TagContainersData->OnHitReact_CancelTags;
	}

protected:
	UPROPERTY()
	TObjectPtr<UDataAsset_GameplayTagContainers> TagContainersData;
};
