

#pragma once

#include "CoreMinimal.h"
#include "System/Subsystem/MusicManager/Playback/MusicPlayback.h"
#include "Data/Music/DataAsset_QuartzMusic.h"
#include "QuartzPlayback.generated.h"

class UQuartzClockHandle;
struct FQuartzQuantizedCommandDelegateData;

UCLASS()
class PORTFOLIO_API AQuartzPlayback : public AMusicPlayback
{
	GENERATED_BODY()
	
public:
	AQuartzPlayback();

protected:
	virtual void BeginPlay() override;



public:
	
	virtual void StartPlayMusic() override;
	virtual void EndPlayMusic() override;

private:
	UFUNCTION()
	void OnQuantizationEvent(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars,
		int32 Beat, float BeatFraction);

	UFUNCTION()
	void OnAudioFinished();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataAsset_QuartzMusic> QuartzData;

protected:
	UPROPERTY()
	UQuartzClockHandle* ClockHandle;

	int32 EventIndex;
	TMap<FName, TObjectPtr<UAudioComponent>> Audios;
	float SecondsPerBeat;
};
