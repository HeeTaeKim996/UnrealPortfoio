

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "System/R1GameplayTags.h"
#include "R1AssetData.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> AssetLabels;
};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;
};

UCLASS()
class PORTFOLIO_API UR1AssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	FSoftObjectPath GetAssetPathByName(const FGameplayTag& AssetName);
	const FAssetSet& GetAssetSetByLabel(const FGameplayTag& Label);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAssetSet> AssetGroupNameToSet;

	UPROPERTY()
	TMap<FGameplayTag, FSoftObjectPath> AssetNameToPath;

	UPROPERTY()
	TMap<FGameplayTag, FAssetSet> AssetLabelToSet;
};