


#include "Data/Music/DataAsset_Music.h"
#include "UObject/ObjectSaveContext.h"

#if WITH_EDITOR
void UDataAsset_Music::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property == nullptr ?
		NAME_None : PropertyChangedEvent.Property->GetFName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UDataAsset_Music, Events))
	{
		SortEvents();
	}
}
void UDataAsset_Music::PreSave(FObjectPreSaveContext SaveContext)
{
	SortEvents();
}


void UDataAsset_Music::SortEvents()
{
	Events.Sort([](const FMusicBarEvent& A, const FMusicBarEvent& B)
		{
			return A.Bar < B.Bar;
		});
}
#endif
