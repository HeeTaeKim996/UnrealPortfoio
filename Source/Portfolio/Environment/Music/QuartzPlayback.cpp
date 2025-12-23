


#include "Environment/Music/QuartzPlayback.h"
#include "System/R1GameplayTags.h"

#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "Components/AudioComponent.h"

AQuartzPlayback::AQuartzPlayback()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;
	ClockHandle = nullptr;
}

void AQuartzPlayback::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(QuartzData, TEXT("Quartz Data is Not assigned"));

	for (const FGameplayTag& Stem : QuartzData->Stems)
	{
		if (Audios.Contains(Stem) == false)
		{
			UAudioComponent* AudioComp = NewObject<UAudioComponent>(this);
			AudioComp->RegisterComponent();
			AudioComp->bAutoActivate = false;

			Audios.Add(Stem, AudioComp);
		}
	}

}

void AQuartzPlayback::StartPlayMusic()
{
	Super::StartPlayMusic();

	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(GetWorld());
	if (QuartzSubsystem == nullptr) return;

	const FName ClockName =
		MakeUniqueObjectName(GetWorld(), UQuartzClockHandle::StaticClass(),
			TEXT("QuartsMusicClock"));
	if (QuartzSubsystem->DoesClockExist(this, ClockName) == true) return;

	FQuartzTimeSignature TimeSignature;
	TimeSignature.NumBeats = 4;
	TimeSignature.BeatType = EQuartzTimeSignatureQuantization::QuarterNote;

	FQuartzClockSettings ClockSettings;
	ClockSettings.TimeSignature = TimeSignature;
	ClockSettings.bIgnoreLevelChange = false;

	ClockHandle = QuartzSubsystem->CreateNewClock(this, ClockName, ClockSettings, true, true);
	if (ClockHandle == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::None;
	SecondsPerBeat = 60.f / QuartzData->BPM;

	FOnQuartzCommandEventBP Delegate;

	ClockHandle->SetBeatsPerMinute(this, Boundary, Delegate, ClockHandle, QuartzData->BPM);

	FOnQuartzMetronomeEventBP EventDelegate;
	EventDelegate.BindUFunction(this, TEXT("OnQuantizationEvent"));


	const EQuartzUnitType& QuartzUnitType = QuartzData->UnitType;
	if (QuartzUnitType == EQuartzUnitType::Bar)
	{
		ClockHandle->SubscribeToQuantizationEvent(this, EQuartzCommandQuantization::Bar, EventDelegate, ClockHandle);
	}
	else if(QuartzUnitType == EQuartzUnitType::Beat)
	{
		ClockHandle->SubscribeToQuantizationEvent(this, EQuartzCommandQuantization::Beat, EventDelegate, ClockHandle);
	}
	else
	{
		ensureAlwaysMsgf(false, TEXT("Not Assigend Unit"));
	}



	ClockHandle->StartClock(this, ClockHandle);
	EventIndex = 0;
}

void AQuartzPlayback::EndPlayMusic()
{
	EndPlayMusic();

}

void AQuartzPlayback::OnQuantizationEvent(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction)
{
}

