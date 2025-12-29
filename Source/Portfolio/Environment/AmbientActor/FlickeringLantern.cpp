


#include "Environment/AmbientActor/FlickeringLantern.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"

AFlickeringLantern::AFlickeringLantern()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	LanternMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
	LanternMesh->SetupAttachment(Root);

	FlickeringLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FlickeringLight"));
	FlickeringLight->SetupAttachment(Root);

	SwayTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SwayTimeline"));
	FlickerTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FlickerTimeline"));
}

void AFlickeringLantern::BeginPlay()
{
	Super::BeginPlay();

	FRotator StartRot = GetActorRotation();
	PitchRot = StartRot.Pitch;
	YawRot = StartRot.Yaw;

	ensureAlwaysMsgf(SwayCurveFloat, TEXT("SwayCurveFloat is Not assigned"));
	ensureAlwaysMsgf(FlickerCurveFloat, TEXT("FlickerCurveFloat is Not assigned"));

	FOnTimelineFloat SwayDelegate;
	SwayDelegate.BindUFunction(this, TEXT("OnSwayUpdate")); // ¡Ø Must Concur the func name


	SwayTimeline->AddInterpFloat(SwayCurveFloat, SwayDelegate);
	SwayTimeline->SetLooping(true);
	SwayTimeline->SetPlayRate(1.f);


	FOnTimelineFloat FlickerDelegate;
	FlickerDelegate.BindUFunction(this, TEXT("OnFlickerUpdate")); // ¡Ø Must Concur The Func name
	FlickerTimeline->AddInterpFloat(FlickerCurveFloat, FlickerDelegate);

	FOnTimelineEvent FlickerFinishDelegate;
	FlickerFinishDelegate.BindUFunction(this, TEXT("OnFlickerFinished"));
	FlickerTimeline->SetTimelineFinishedFunc(FlickerFinishDelegate);

	FlickerTimeline->SetLooping(false);
	FlickerTimeline->SetPlayRate(1.f);

	const float WaitTime = FMath::FRandRange(0, 5.f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		[this]()
		{
			SwayTimeline->Play();
			FlickerTimeline->Play();

		}, WaitTime, false);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Begin Check"));
}

void AFlickeringLantern::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}
	if (SwayTimeline)
	{
		SwayTimeline->Stop();
	}
	if (FlickerTimeline)
	{
		FlickerTimeline->Stop();
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("EndPlay Check"));
}


void AFlickeringLantern::OnSwayUpdate(float Value)
{
	Root->SetRelativeRotation(FRotator(PitchRot, YawRot, Value));
}


void AFlickeringLantern::OnFlickerUpdate(float Value)
{
	const float LightIntensity = LightBaseIntensity * Value;
	FlickeringLight->SetIntensity(LightIntensity);
}

void AFlickeringLantern::OnFlickerFinished()
{
	const float WaitTime = FMath::FRandRange(4.f, 8.f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		[this]()
		{
			FlickerTimeline->PlayFromStart();
		},
		WaitTime, false);
}
