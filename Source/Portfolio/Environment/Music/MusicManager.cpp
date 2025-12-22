


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

	Audios.SetNum(static_cast<uint8>(ESoundType::End));

	UGameInstance* GI = GetGameInstance();
	if (GI == nullptr) return;

	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(GetWorld());
	if (QuartzSubsystem == nullptr) return;

	const FName ClockName(TEXT("MusicManagerClock"));
	if (QuartzSubsystem->DoesClockExist(this, ClockName) == true)
	{
		ClockHandle = QuartzSubsystem->GetHandleForClock(this, ClockName);
	}
	else
	{
		FQuartzTimeSignature TimeSignature;
		TimeSignature.NumBeats = 4;
		TimeSignature.BeatType = EQuartzTimeSignatureQuantization::QuarterNote;

		FQuartzClockSettings ClockSettings;
		ClockSettings.TimeSignature = TimeSignature;
		ClockSettings.bIgnoreLevelChange = true;


		ClockHandle = QuartzSubsystem->CreateNewClock(this, ClockName, ClockSettings, true, true);
	}



	if (ClockHandle == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::None;
	const float BPM = 100.f;
	SecondsPerBeat = 60.f / BPM;

	FOnQuartzCommandEventBP Delegate;

	ClockHandle->SetBeatsPerMinute(this, Boundary, Delegate, ClockHandle, BPM);

	ClockHandle->StartClock(this, ClockHandle);
}

void AMusicManager::Test1()
{
	if (ClockHandle == nullptr) return;

	if (T1Sound == nullptr) return;


	Sound1 = UGameplayStatics::CreateSound2D(this, T1Sound, 1.f, 1.f, 0, nullptr, false, false);
	if (Sound1 == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::Beat;
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
	Boundary.Quantization = EQuartzCommandQuantization::Beat;
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

void AMusicManager::Test4()
{
	PlaySound(T1Sound, ESoundType::MainTheme, 1.f, 1.f, 2.f);
}

void AMusicManager::Test5()
{
	PlaySound(T2Sound, ESoundType::MainTheme, 1.f, 1.f, 2.f);
}

void AMusicManager::PlaySound(USoundBase* NewSound, ESoundType SoundType, float FadeOut, float FadeIn, 
	float FadeInStart)
{
	TObjectPtr<UAudioComponent>& Audio = Audios[static_cast<uint8>(SoundType)];

	if (Audio)
	{
		Audio->FadeOut(FadeOut, 0.f); // ¡Ø Unit : Second
	}

	if (NewSound == nullptr) return;

	Audio = UGameplayStatics::CreateSound2D(this, NewSound, 1.f, 1.f, 0, nullptr, false, false);
	if (Audio == nullptr) return;

	FQuartzQuantizationBoundary Boundary;
	Boundary.Quantization = EQuartzCommandQuantization::Beat;
	Boundary.Multiplier = FadeInStart / SecondsPerBeat; // ¡Ø Unit : Beat
	Boundary.CountingReferencePoint = EQuarztQuantizationReference::TransportRelative;

	FOnQuartzCommandEventBP Delegate;

	Audio->PlayQuantized(this, ClockHandle, Boundary, Delegate, 0.f, FadeIn, 1.f, EAudioFaderCurve::Linear);
	// ¡Ø FadeIn's Unit : Second
}


