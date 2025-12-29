


#include "AI/UpdateActivateTime.h"
#include "BehaviorTree/BlackboardComponent.h"

UUpdateActivateTime::UUpdateActivateTime()
{
	NodeName = TEXT("UpdateActivateTime");
	Interval = 1.f;
}

void UUpdateActivateTime::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	float ActivateTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ActivateTimeKey.SelectedKeyName);
	ActivateTime -= 1.f;

	if (ActivateTime <= 0.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
		
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ActivateTimeKey.SelectedKeyName, ActivateTime);
}
