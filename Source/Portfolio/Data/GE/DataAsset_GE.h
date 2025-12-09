

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_GE.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UDataAsset_GE : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> GE;
};
