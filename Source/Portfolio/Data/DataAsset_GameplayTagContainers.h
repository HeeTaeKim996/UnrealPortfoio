

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
	UDataAsset_GameplayTagContainers();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer BaseAbilityBlockTgs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer OnActionCall_BaseCancelingTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer OnHitReact_CancelTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer PlayerNotRegenableTags;
};