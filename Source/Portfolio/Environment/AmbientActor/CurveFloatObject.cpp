


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

	ensureAlwaysMsgf(Curve, TEXT("Curve is Not assigned"));

	CurveTimeline = NewObject<UTimelineComponent>(this, TEXT("Timeline"));
	CurveTimeline->RegisterComponent();



	FOnTimelineFloat UpdateDelegate;

	UpdateDelegate.BindUFunction(this, TEXT("OnCurveTimeUpdate"));


	CurveTimeline->AddInterpFloat(Curve, UpdateDelegate);
	CurveTimeline->SetLooping(true);
	CurveTimeline->SetPlayRate(CurveSpeed);
	CurveTimeline->Play();
}

void ACurveFloatObject::OnCurveTimeUpdate(float Value)
{
	const float Rot = Value * CurveIntensity;
	Box->SetRelativeRotation(FRotator(
		bUsePitchRot ?	Rot : 0,
		bUseYawRot ?	Rot : 0, 
		bUseRollRot ?	Rot : 0));
}


