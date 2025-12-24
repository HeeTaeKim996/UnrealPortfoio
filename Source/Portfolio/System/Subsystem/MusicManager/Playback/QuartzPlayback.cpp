


#include "System/Subsystem/MusicManager/Playback/QuartzPlayback.h"
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
}

void AQuartzPlayback::StartPlayMusic()
{
	Super::StartPlayMusic();

	for (const FName& Stem : QuartzData->Stems)
	{
		if (Audios.Contains(Stem) == false)
		{
			UAudioComponent* AudioComp = NewObject<UAudioComponent>(this);
			AudioComp->RegisterComponent();
			AudioComp->bAutoActivate = false;

			Audios.Add(Stem, AudioComp);


			AudioComp->OnAudioFinished.AddDynamic(this, &AQuartzPlayback::OnAudioFinished);
		}
	}

	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(GetWorld());
	if (QuartzSubsystem == nullptr) return;

	const FName ClockName = MakeUniqueObjectName(GetWorld(), UQuartzClockHandle::StaticClass(),
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
	else if (QuartzUnitType == EQuartzUnitType::Beat)
	{
		ClockHandle->SubscribeToQuantizationEvent(this, EQuartzCommandQuantization::Beat, EventDelegate, ClockHandle);
	}


	EventIndex = 0;
	ClockHandle->StartClock(this, ClockHandle);
}

void AQuartzPlayback::EndPlayMusic()
{
	if (ClockHandle)
	{
		if (UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(GetWorld()))
		{
			QuartzSubsystem->DeleteClockByHandle(this, ClockHandle);
		}
		ClockHandle = nullptr;
	}


	for (auto& Pair : Audios)
	{
		Pair.Value->DestroyComponent();
		Pair.Value->OnAudioFinished.RemoveDynamic(this, &AQuartzPlayback::OnAudioFinished);
	}
	Audios.Empty();

	


	Super::EndPlayMusic();
}

void AQuartzPlayback::OnQuantizationEvent(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars,
	int32 Beat, float BeatFraction)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan,
		FString::Printf(TEXT("QuartzPlayback.cpp : [%d], [%d]"), NumBars, Beat));

	TArray<FMusicBarEvent>& Events = QuartzData->Events;
	ensureAlwaysMsgf(Events.IsEmpty() == false, TEXT("Event Is Empty"));

	int CurrentUnit = QuartzData->UnitType == EQuartzUnitType::Bar ? NumBars : NumBars * 4 + Beat;

	
#if 1
	if (EventIndex == Events.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("SameNum"));
	}
	else if (Events[EventIndex].Unit > CurrentUnit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, 
			FString::Printf(TEXT("Unit : [%d], [%d]"), Events[EventIndex].Unit, CurrentUnit));
	}

#endif


	while (EventIndex < Events.Num() && Events[EventIndex].Unit <= CurrentUnit)
	{
		const FMusicBarEvent& MusicBarEvent = Events[EventIndex++];

		const FName& MusicStem = MusicBarEvent.Stem;

		ensureAlwaysMsgf(Audios.Contains(MusicStem), TEXT("Not assigned music stem"));

		TObjectPtr<UAudioComponent>& Audio = Audios[MusicStem];
		if (Audio->IsPlaying())
		{
			Audio->Stop();
		}

		if (MusicBarEvent.Sound == nullptr) continue;
		Audio->SetSound(MusicBarEvent.Sound);


		FQuartzQuantizationBoundary Boundary;
		Boundary.Quantization = EQuartzCommandQuantization::Beat;
		Boundary.Multiplier = 1.f;
		Boundary.CountingReferencePoint = EQuarztQuantizationReference::TransportRelative;

		FOnQuartzCommandEventBP Delegate;

		Audio->PlayQuantized(this, ClockHandle, Boundary, Delegate, 0.f, 0.f, 1.f, EAudioFaderCurve::Linear);



	}
}

void AQuartzPlayback::OnAudioFinished()
{
	if (EventIndex < QuartzData->Events.Num()) return;

	bool IsAllFinished = true;
	for (auto& Pair : Audios)
	{
		if (Pair.Value->IsPlaying() == true)
		{
			IsAllFinished = false;
			break;
		}
	}

	if (IsAllFinished == true)
	{
		EndPlayMusic();

		// TEMP
		{
			StartPlayMusic();
		}
	}
}

