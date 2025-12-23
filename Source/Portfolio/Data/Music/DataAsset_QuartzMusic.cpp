


#include "Data/Music/DataAsset_QuartzMusic.h"
#include "UObject/ObjectSaveContext.h"


void UDataAsset_QuartzMusic::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property == nullptr ?
		NAME_None : PropertyChangedEvent.Property->GetFName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UDataAsset_QuartzMusic, Events))
	{
		SortEvents();
	}
}

void UDataAsset_QuartzMusic::PreSave(FObjectPreSaveContext SaveContext)
{
	SortEvents();
}


void UDataAsset_QuartzMusic::SortEvents()
{
	Events.Sort([](const FMusicBarEvent& A, const FMusicBarEvent& B)
		{
			return A.Unit < B.Unit;
		});
}