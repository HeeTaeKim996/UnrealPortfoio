

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_GameplayTagContainers.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UDataAsset_GameplayTagContainers : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer CantBaseActableTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer OnActionCall_CancelingTags;
};
