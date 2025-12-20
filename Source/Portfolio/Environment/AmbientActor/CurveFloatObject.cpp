


#include "Environment/AmbientActor/CurveFloatObject.h"

ACurveFloatObject::ACurveFloatObject()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Box = CreateDefaultSubobject<USceneComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Box);
}

void ACurveFloatObject::BeginPlay()
{
	Super::BeginPlay();

	FRotator StartRot = GetActorRotation();
	PitchRot = StartRot.Pitch;
	YawRot = StartRot.Yaw;


	ensureAlwaysMsgf(Curve, TEXT("Curve is Not assigned"));




	FOnTimelineFloat UpdateDelegate;

	UpdateDelegate.BindUFunction(this, TEXT("OnCurveTimeUpdate")); // ¡Ø Must Match Function Name

	CurveTimeline = NewObject<UTimelineComponent>(this, TEXT("Timeline"));
	CurveTimeline->RegisterComponent();

	CurveTimeline->AddInterpFloat(Curve, UpdateDelegate);
	CurveTimeline->SetLooping(true);
	CurveTimeline->SetPlayRate(CurveSpeed);

	const float WaitTime = FMath::FRandRange(0.f, 5.f);
	GetWorld()->GetTimerManager().SetTimer(SwayTimerHandle,
		[this]()
		{
			CurveTimeline->Play();
		}
		, WaitTime, false);
}

void ACurveFloatObject::OnCurveTimeUpdate(float Value)
{
	const float Roll = Value * CurveIntensity;
	Box->SetRelativeRotation(FRotator(PitchRot, YawRot, Roll));
}


