


#include "Environment/AmbientCharacter/Crow/AI_AmbientCrow.h"
#include "Environment/AmbientCharacter/Crow/AmbientCrow.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Environment/AmbientCharacter/Crow/Anim_Crow.h"
#include "Components/ArrowComponent.h"

AAI_AmbientCrow::AAI_AmbientCrow()
	: Super()
{

}

void AAI_AmbientCrow::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(CrowTimerHandle, this, &AAI_AmbientCrow::DoRoam, 0.1f, false);
}

void AAI_AmbientCrow::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Crow = Cast<AAmbientCrow>(GetPawn());
	ensureAlwaysMsgf(Crow, TEXT("NotCrow"));

	
	StartPos = Crow->GetActorLocation();
	RoamAimPos = StartPos;
	UCharacterMovementComponent* CharacterMovement = Crow->GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = 50.f;

	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0, 620.f, 0);
	Crow->bUseControllerRotationYaw = false;

	CharacterMovement->MaxFlySpeed = 1000.f;


	FlyingDir = Crow->FlyDirectionArrow->GetForwardVector();
	FlyingDir.Z = 0;
	FlyingDir.Normalize();
}

void AAI_AmbientCrow::EndPlay(const EEndPlayReason::Type EndReason)
{
	Super::EndPlay(EndReason);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(CrowTimerHandle);
	}
}



void AAI_AmbientCrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFlying)
	{
		FlyElapsed += DeltaTime;

		if (FlyElapsed > 5.f)
		{
			Crow->Destroy();
			return;
		}

		Crow->AddMovementInput(FlyingDir, 1.f);
		
		if (HeightUp < 3.f)
		{
			float Up = 0.1f;
			float UpScale = Up * DeltaTime;
			HeightUp += UpScale;

			Crow->AddMovementInput(FVector::UpVector, Up);
		}
	}
}



void AAI_AmbientCrow::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	const float WaitTime = FMath::FRandRange(2.f, 6.f);
	GetWorld()->GetTimerManager().SetTimer(CrowTimerHandle, this, &AAI_AmbientCrow::DoRoam, WaitTime, false);
}

void AAI_AmbientCrow::DoRoam()
{
	FNavLocation NavLocation;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	bool bSucceed;
	float SearchAddableRadius = 0.f;
	do
	{
		bSucceed = NavSys->GetRandomReachablePointInRadius(StartPos, RoamRadius + SearchAddableRadius, NavLocation);
		SearchAddableRadius += 2.f;
	} while (bSucceed == false && SearchAddableRadius < 20.f);

	ensureAlwaysMsgf(bSucceed, TEXT("Cant Find Place To go"));

	RoamAimPos = NavLocation.Location;

	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(RoamAimPos);
	MoveReq.SetAcceptanceRadius(5.f);
	MoveReq.SetUsePathfinding(true);

	MoveTo(MoveReq);
}

void AAI_AmbientCrow::StartFly()
{
	StopMovement();
	bIsFlying = true;

	UCharacterMovementComponent* MoveComponent = Crow->GetCharacterMovement();
	MoveComponent->GravityScale = 0.f;
	MoveComponent->SetMovementMode(MOVE_Flying);


	UCapsuleComponent* Capsule = Crow->GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (USkeletalMeshComponent* Mesh = Crow->GetMesh())
	{
		if (UAnim_Crow* CrowAnim = Cast<UAnim_Crow>(Mesh->GetAnimInstance()))
		{
			CrowAnim->SetFly();
		}
	}
}
