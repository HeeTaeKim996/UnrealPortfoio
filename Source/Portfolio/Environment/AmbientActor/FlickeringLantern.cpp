


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

	SwayTimeline = NewObject<UTimelineComponent>(this, TEXT("SwayTimeline"));
	SwayTimeline->RegisterComponent();

	SwayTimeline->AddInterpFloat(SwayCurveFloat, SwayDelegate);
	SwayTimeline->SetLooping(true);
	SwayTimeline->SetPlayRate(1.f);




	FlickerTimeline = NewObject<UTimelineComponent>(this, TEXT("FlickerTimeline"));
	FlickerTimeline->RegisterComponent();

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
