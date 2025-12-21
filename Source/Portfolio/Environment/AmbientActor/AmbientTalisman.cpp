


#include "Environment/AmbientActor/AmbientTalisman.h"



AAmbientTalisman::AAmbientTalisman()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
}

void AAmbientTalisman::BeginPlay()
{
	Super::BeginPlay();

	//ensureAlwaysMsgf(FC_SideToSide && FC_Sway && FC_BackAndForth, TEXT("FC is Not assigned"));
	ensureAlwaysMsgf(FC_Vector, TEXT("FC Vector is Not assigned"));

	RotateTimeline = NewObject<UTimelineComponent>(this, TEXT("RotateTimeline"));
	RotateTimeline->RegisterComponent();

	FOnTimelineVector Delegate_TimelineVector;
	Delegate_TimelineVector.BindUFunction(this, TEXT("OnTimelineVectorUpdate"));
	RotateTimeline->AddInterpVector(FC_Vector, Delegate_TimelineVector);

	RotateTimeline->SetLooping(true);

	RotateTimeline->Play();
}


void AAmbientTalisman::OnTimelineVectorUpdate(FVector Vector)
{
	Root->SetRelativeRotation(FRotator(Vector.X, Vector.Y, Vector.Z));
	
}
