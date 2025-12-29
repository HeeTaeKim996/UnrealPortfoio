


#include "AI/FieldMonster/FieldMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

AFieldMonsterController::AFieldMonsterController()
	: Super()
{
}

void AFieldMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		const FVector OriginalPos = InPawn->GetActorLocation();
		BB->SetValueAsVector(TEXT("OriginalPos"), OriginalPos);
	}
}
