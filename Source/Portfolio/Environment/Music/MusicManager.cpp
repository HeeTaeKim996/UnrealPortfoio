


#include "Environment/Music/MusicManager.h"
#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "Components/AudioComponent.h"


AMusicManager::AMusicManager()
{
	PrimaryActorTick.bCanEverTick = false;
	ClockHandle = nullptr;
}

void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Start1"));

	UGameInstance* GI = GetGameInstance();
	if (GI == nullptr) return;

	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(GetWorld());
	if (QuartzSubsystem == nullptr) return;

	FQuartzTimeSignature TimeSignature;
	TimeSignature.NumBeats = 4;
	TimeSignature.BeatType = EQuartzTimeSignatureQuantization::QuarterNote;

	FQuartzClockSettings ClockSettings;
	ClockSettings.TimeSignature = TimeSignature;
	ClockSettings.bIgnoreLevelChange = true; // ¡Ø May MusicManager doest need to be AActor ? or Can Move To Other Level?

	const FName ClockName(TEXT("MusicManagerClock"));
	ClockHandle = QuartzSubsystem->CreateNewClock(this, ClockName, ClockSettings, true, true);

	if (ClockHandle == nullptr) return;


	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::None;
	const float BPM = 100.f;
	FOnQuartzCommandEventBP Delegate; 

	ClockHandle->SetBeatsPerMinute(this, Boundary, Delegate, ClockHandle, BPM);

	ClockHandle->StartClock(this, ClockHandle);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Start2"));
}

void AMusicManager::Test1()
{
	if (ClockHandle == nullptr) return;

	if (T1Sound == nullptr) return;


	Sound1 = UGameplayStatics::CreateSound2D(this, T1Sound, 1.f, 1.f, 0, nullptr, false, false);
	if (Sound1 == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::Bar;
	Boundary.Multiplier = 1.f;
	Boundary.CountingReferencePoint = EQuarztQuantizationReference::TransportRelative;

	FOnQuartzCommandEventBP Delegate;

	Sound1->PlayQuantized(this, ClockHandle, Boundary, Delegate, 0.f, 0.f, 1.f, EAudioFaderCurve::Linear);
}

void AMusicManager::Test2()
{
	if (ClockHandle == nullptr) return;

	if (T2Sound == nullptr) return;

	Sound2 = UGameplayStatics::CreateSound2D(this, T2Sound, 1.f, 1.f, 0, nullptr, false, false);
	if (Sound2 == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::Bar;
	Boundary.Multiplier = 1.f;
	Boundary.CountingReferencePoint = EQuarztQuantizationReference::TransportRelative;

	FOnQuartzCommandEventBP Delegate;

	Sound2->PlayQuantized(this, ClockHandle, Boundary, Delegate, 0.f, 0.f, 1.f, EAudioFaderCurve::Linear);
}

void AMusicManager::Test3()
{
	if (Sound1)
	{
		Sound1->Stop();
	}
	if (Sound2)
	{
		Sound2->Stop();
	}
}


