

#include "System/R1AssetManager.h"
#include "ETC/R1LogChannels.h"

UR1AssetManager::UR1AssetManager() : Super()
{
}

UR1AssetManager& UR1AssetManager::Get()
{
	if (UR1AssetManager* SingleTon = Cast<UR1AssetManager>(GEngine->AssetManager))
	{
		return *SingleTon;
	}

	UE_LOG(LogR1, Fatal, TEXT("Can't Find UR1AssetManager"));
	return *NewObject<UR1AssetManager>();
}

void UR1AssetManager::Initialize() // Invoke From R1GameInstance
{
	Get().LoadPreloadAssets();
}








/* Sync Load */
void UR1AssetManager::LoadSyncByPath(const FSoftObjectPath& AssetPath, const FGameplayTag& AssetName)
{
	if (AssetPath.IsValid())
	{
		UObject* LoadedAsset = AssetPath.ResolveObject();
		if (LoadedAsset == nullptr)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false); // Sync Instan UObject
			}
			else
			{
				LoadedAsset = AssetPath.TryLoad(); // ※ Low-Level Operation Load
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAsset(AssetName, LoadedAsset);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed To Load Asset [%s]."), *AssetPath.ToString());
		}
	}
}

void UR1AssetManager::LoadSyncByName(const FGameplayTag& AssetName)
{
	UR1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadSyncByPath(AssetPath, AssetName);
}

void UR1AssetManager::LoadSyncByLabel(const FGameplayTag& Label)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager  must be initialized"));
		return;
	}

	UR1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;
	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabel(Label);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			AssetPaths.Emplace(AssetPath);
		}
	}
	GetStreamableManager().RequestSyncLoad(AssetPaths);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			if (UObject* LoadedAsset = AssetPath.ResolveObject())
			{
				Get().AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Failed To Load Asset [%s]."), *AssetPath.ToString());
			}
		}
	}
}











/* Async Load */
void UR1AssetManager::LoadAsyncByPath(const FSoftObjectPath& AssetPath, const FGameplayTag& AssetName,
	FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be Initialized"));
		return;
	}

	if (AssetPath.IsValid())
	{
		if (UObject* LoadedAsset = AssetPath.ResolveObject())
		{
			Get().AddLoadedAsset(AssetName, LoadedAsset);
		}
		else
		{
			TArray<FSoftObjectPath> AssetPaths;
			AssetPaths.Add(AssetPath);

			TSharedPtr<FStreamableHandle> Handle = GetStreamableManager().RequestAsyncLoad(AssetPaths);

			Handle->BindCompleteDelegate(FStreamableDelegate::CreateLambda
			(
				[AssetName, AssetPath, CompleteDelegate = MoveTemp(CompletedDelegate)]()
				{
					UObject* LoadedAsset = AssetPath.ResolveObject();
					Get().AddLoadedAsset(AssetName, LoadedAsset);
					if (CompleteDelegate.IsBound()) CompleteDelegate.Execute(AssetName, LoadedAsset);
				}
			));
		}
	}
}

void UR1AssetManager::LoadAsyncByName(const FGameplayTag& AssetName, FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be Initialized"));
		return;
	}

	UR1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadAsyncByPath(AssetPath, AssetName, CompletedDelegate);
}

void UR1AssetManager::LoadAsyncByLabel(const FGameplayTag& Label, FAsncLoadCompleteLabelDelegate CompleteDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager  must be initialized"));
		return;
	}
	UR1AssetManager& AssetManager = Get();
	UR1AssetData* AssetData = AssetManager.LoadedAssetData;
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;
	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabel(Label);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			AssetPaths.Add(AssetPath);
		}
	}

	TSharedPtr<FStreamableHandle> Handle = GetStreamableManager().RequestAsyncLoad(AssetPaths);

	Handle->BindCompleteDelegate(FStreamableDelegate::CreateLambda
	(
		[&AssetManager, &AssetSet, Label, CompleteDelegate = MoveTemp(CompleteDelegate)]() 
		{
			for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
			{
				const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
				UObject* LoadedAsset = AssetPath.ResolveObject();
				AssetManager.AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}

			if (CompleteDelegate.IsBound()) CompleteDelegate.Execute(Label);
		}
	));
}







/* Release */
void UR1AssetManager::ReleaseByName(const FGameplayTag& AssetName)
{
	UR1AssetManager& AssetManager = Get();
	if (AssetManager.NameToLoadedAsset.Contains(AssetName))
	{
		AssetManager.NameToLoadedAsset.Remove(AssetName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by AssetName [%s]."), *AssetName.ToString());
	}
}

void UR1AssetManager::ReleaseByLabel(const FGameplayTag& Label)
{
	UR1AssetManager& AssetManager = Get();
	UR1AssetData* LoadedAssetData = AssetManager.LoadedAssetData;
	const FAssetSet& AssetSet = LoadedAssetData->GetAssetSetByLabel(Label);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FGameplayTag& AssetName = AssetEntry.AssetName;
		if (AssetManager.NameToLoadedAsset.Contains(AssetName))
		{
			AssetManager.NameToLoadedAsset.Remove(AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
		}
	}
}





/* Primary */
void UR1AssetManager::AddLoadedAsset(const FGameplayTag& AssetName, const UObject* Asset)
{
	if (AssetName.IsValid() && Asset)
	{
		if (NameToLoadedAsset.Contains(AssetName) == false)
		{
			NameToLoadedAsset.Add(AssetName, Asset);
		}
	}
}

void UR1AssetManager::LoadPreloadAssets()
{
	if (LoadedAssetData) return;

	UR1AssetData* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UR1AssetData::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UR1AssetData>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		LoadedAssetData = AssetData;
		LoadSyncByLabel(R1Tags::Asset_Label_Preload);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load AssetData asset type [%s]."), *PrimaryAssetType.ToString());
	}
}