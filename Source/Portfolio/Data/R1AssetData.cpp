


#include "Data/R1AssetData.h"
#include "UObject/ObjectSaveContext.h"


void UR1AssetData::PreSave(FObjectPreSaveContext ObjectSaveContext) // Invoked When AssetSaved In Editor
{
	Super::PreSave(ObjectSaveContext);

	AssetNameToPath.Empty();
	AssetLabelToSet.Empty();

	AssetGroupNameToSet.KeySort( // ※ Unlike map or unordered_map, TMap can sort ( but Insert/Remove breaks order )
		[](const FName& a, const FName& b)
		{
			return a.Compare(b) < 0;
		}
	);

	for (const auto& Pair : AssetGroupNameToSet)
	{
		const FAssetSet& AssetSet = Pair.Value;
		for (FAssetEntry AssetEntry : AssetSet.AssetEntries)
		{
			FSoftObjectPath& AssetPath = AssetEntry.AssetPath;

			AssetNameToPath.Emplace(AssetEntry.AssetName, AssetEntry.AssetPath);
			for (const FGameplayTag& Label : AssetEntry.AssetLabels)
			{
				AssetLabelToSet.FindOrAdd(Label).AssetEntries.Emplace(AssetEntry);
			}
		}
	}
}

FSoftObjectPath UR1AssetData::GetAssetPathByName(const FGameplayTag& AssetName)
{
	FSoftObjectPath* AssetPath = AssetNameToPath.Find(AssetName);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't find asset path from Asset Name [%s]."), *AssetName.ToString());
	// ※ ensureAlwaysMsgf : Like F9, Pause (Can Resume). Also Log

	return *AssetPath;
}

const FAssetSet& UR1AssetData::GetAssetSetByLabel(const FGameplayTag& Label)
{
	const FAssetSet* AssetSet = AssetLabelToSet.Find(Label);
	ensureAlwaysMsgf(AssetSet, TEXT("Can't find Asest Set from Label[%s]."), *Label.ToString());

	return *AssetSet;
}