

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Data_InitializeGEs.generated.h"

class UGameplayEffect;


USTRUCT()
struct FInitializeGe
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GE;
};

UCLASS()
class PORTFOLIO_API UData_InitializeGEs : public UDataAsset
{
	GENERATED_BODY()
public:
	TSubclassOf<UGameplayEffect> FindGEByTag(const FGameplayTag& InputTag) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FInitializeGe> InitializeGes;
};
