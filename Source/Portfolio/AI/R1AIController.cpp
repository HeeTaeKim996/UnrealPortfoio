


#include "AI/R1AIController.h"
#include "Navigation/PathFollowingComponent.h"

AR1AIController::AR1AIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void AR1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AR1AIController::BeginPlay()
{
	Super::BeginPlay();


}

void AR1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
