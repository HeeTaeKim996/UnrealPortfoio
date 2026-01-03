


#include "AI/FieldMonster/BTService_OnNoTarget.h"
#include "AI/FieldMonster/FieldMonsterController.h"
#include "Character/R1Character.h"
#include "Character/R1Player.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/FieldMonster.h" 


UBTService_OnNoTarget::UBTService_OnNoTarget()
{
	NodeName = TEXT("OnNoTarget");
	Interval = 0.3f;
	bNotifyBecomeRelevant = true;
}

void UBTService_OnNoTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	CachedSearchRadiusSquared = static_cast<double>(SearchRadius) * SearchRadius;
}

void UBTService_OnNoTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return;

	UWorld* World = OwnerPawn->GetWorld();
	if (World == nullptr) return;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	FVector Location = OwnerPawn->GetActorLocation();

	AR1Character* PlayerCharacter = Cast<AR1Character>(World->GetFirstPlayerController()->GetPawn());
#if 0
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("Player=%d"),
		PlayerCharacter != nullptr));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Dead=%d"), 
		PlayerCharacter ? PlayerCharacter->IsInState(R1Tags::Ability_Dead) : -1));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("DistSq=%.1f / RadiusSq=%.1f"), 
		PlayerCharacter ? FVector::DistSquared(Location, PlayerCharacter->GetActorLocation()) : -1.f, 
		CachedSearchRadiusSquared));
#endif

	if (PlayerCharacter && 
		PlayerCharacter->IsInState(R1Tags::Ability_Dead) == false &&
		FVector::DistSquared(Location, PlayerCharacter->GetActorLocation()) < CachedSearchRadiusSquared)
	{
		BlackboardComponent->SetValueAsObject(TargetKey.SelectedKeyName, PlayerCharacter);
		BlackboardComponent->SetValueAsFloat(ActivateTimeKey.SelectedKeyName, ActivateTime);
		if (AFieldMonster* FieldMonster = Cast<AFieldMonster>(OwnerPawn))
		{
			FieldMonster->DoWork();
		}
#if 1
		DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f);
#endif
	}
	else
	{
		BlackboardComponent->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);

		bool bIsLeaveWorkable = FVector::DistSquared(OwnerPawn->GetActorLocation(),
			BlackboardComponent->GetValueAsVector(OriginalPosKey.SelectedKeyName)) < 1600.0;
		BlackboardComponent->SetValueAsBool(IsLeaveWorkableKey.SelectedKeyName, bIsLeaveWorkable);

#if 1
		{
			const FVector Curr = OwnerPawn->GetActorLocation();
			const FVector Orig = BlackboardComponent->GetValueAsVector(OriginalPosKey.SelectedKeyName);
			const float DistSq = FVector::DistSquared(Curr, Orig);

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("BTService_OnNoTarget.cpp ~~ "));
			GEngine->AddOnScreenDebugMessage(
				-1, 1.f, FColor::Cyan,
				FString::Printf(TEXT("Curr=(%.1f, %.1f, %.1f)"), Curr.X, Curr.Y, Curr.Z));

			GEngine->AddOnScreenDebugMessage(
				-1, 1.f, FColor::Yellow,
				FString::Printf(TEXT("Orig=(%.1f, %.1f, %.1f)"), Orig.X, Orig.Y, Orig.Z));

			GEngine->AddOnScreenDebugMessage(
				-1, 1.f, FColor::Green,
				FString::Printf(TEXT("DistSq=%.1f"), DistSq));
		}
#endif


		if (AFieldMonster* FieldMonster = Cast<AFieldMonster>(OwnerPawn))
		{
			if (bIsLeaveWorkable && FieldMonster->IsWorking() == true)
			{
				FieldMonster->LeaveWork();
			}
		}

#if 1
		DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f);
#endif
	}
}
