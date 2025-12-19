

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Data/R1AssetData.h"
#include "System/R1GameplayTags.h"
#include "R1AssetManager.generated.h"

class UObject;

DECLARE_DELEGATE_TwoParams(FAsyncLoadCompletedDelegate, const FGameplayTag&/*AssetName or Label*/, UObject*/*LoadedAsset*/);
DECLARE_DELEGATE_OneParam(FAsncLoadCompleteLabelDelegate, const FGameplayTag&);

UCLASS()
class PORTFOLIO_API UR1AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UR1AssetManager();

	static UR1AssetManager& Get();

public:
	static void Initialize();

	template<typename AssetType>
	static AssetType* GetAssetByName(const FGameplayTag& AssetName);

	static void LoadSyncByPath(const FSoftObjectPath& AssetPath, const FGameplayTag& AssetName);
	static void LoadSyncByName(const FGameplayTag& AssetName);
	static void LoadSyncByLabel(const FGameplayTag& Label);

	static void LoadAsyncByPath(const FSoftObjectPath& AssetPath, const FGameplayTag& AssetName,
		FAsyncLoadCompletedDelegate CompleteDelegate = FAsyncLoadCompletedDelegate());
	static void LoadAsyncByName(const FGameplayTag& AssetName,
		FAsyncLoadCompletedDelegate CompleteDelegate = FAsyncLoadCompletedDelegate());
	static void LoadAsyncByLabel(const FGameplayTag& Label,
		FAsncLoadCompleteLabelDelegate CompleteDelegate = FAsncLoadCompleteLabelDelegate());

	static void ReleaseByName(const FGameplayTag& AssetName);
	static void ReleaseByLabel(const FGameplayTag& Label);
	static void ReleaseAll();

private:
	void AddLoadedAsset(const FGameplayTag& AssetName, const UObject* Asset);
	
	void LoadPreloadAssets();

private:
	UPROPERTY()
	TObjectPtr<UR1AssetData> LoadedAssetData;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<const UObject>> NameToLoadedAsset;
};


template<typename AssetType>
AssetType* UR1AssetManager::GetAssetByName(const FGameplayTag& AssetName)
{
	UR1AssetManager& AssetManager = Get();

	UR1AssetData* AssetData = AssetManager.LoadedAssetData;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;


	if (AssetManager.NameToLoadedAsset.Contains(AssetName))
	{
		LoadedAsset = Cast<AssetType>(*AssetManager.NameToLoadedAsset.Find(AssetName));
	}
	else
	{
		const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
		if (AssetPath.IsValid())
		{
			LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());
			if (LoadedAsset == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Attempted sync loading because asset hadn't loaded yet [%s]."),
					*AssetPath.ToString());
				LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
			}
		}
	}
	
	return LoadedAsset;
}