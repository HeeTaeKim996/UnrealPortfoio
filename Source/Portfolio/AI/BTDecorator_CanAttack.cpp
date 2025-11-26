


#include "AI/BTDecorator_CanAttack.h"
#include "R1AIController.h"
#include "Character/R1Player.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_CanAttack::UBTDecorator_CanAttack() 
	: Super()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return false;

	AR1Player* PlayerCh = Cast<AR1Player>(OwnerComp.GetBlackboardComponent()
		->GetValueAsObject(TargetKey.SelectedKeyName));
	if (PlayerCh == nullptr) return false;

	return PlayerCh->GetDistanceTo(ControllingPawn) <= AttackableRange;
}
