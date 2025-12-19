


#include "AI/BTService_FindTarget.h"
#include  "R1AIController.h"
#include "Character/R1Character.h"
#include "Character/R1Player.h"

#include "BehaviorTree/BlackboardComponent.h"
 

UBTService_FindTarget::UBTService_FindTarget()
	: Super()
{
	NodeName = TEXT("FindTargetService");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return;

	UWorld* World = OwnerPawn->GetWorld();
	if (World == nullptr) return;

	FVector Location = OwnerPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, OwnerPawn);

	bool bResult = World->OverlapMultiByChannel(OverlapResults, Location, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel14, FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam);

	if (bResult)
	{
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			AR1Player* PlayerCharacter = Cast<AR1Player>(OverlapResult.GetActor());

			if (PlayerCharacter)
			{
				OwnerComp.GetBlackboardComponent()
					->SetValueAsObject(TargetKey.SelectedKeyName, PlayerCharacter);

				DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
		DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f);
	}

}
