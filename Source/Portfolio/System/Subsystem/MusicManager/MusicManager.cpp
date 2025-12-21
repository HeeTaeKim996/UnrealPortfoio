


#include "System/Subsystem/MusicManager/MusicManager.h"
#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Sound/QuartzQuantizationUtilities.h"

void UMusicManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


}

void UMusicManager::Deinitialize()
{
	Super::Deinitialize();

}

UMusicManager* UMusicManager::Get(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UMusicManager>();
	}
	return nullptr;
}