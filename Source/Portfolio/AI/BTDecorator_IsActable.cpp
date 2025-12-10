


#include "AI/BTDecorator_IsActable.h"
#include "R1AIController.h"
#include "Character/R1Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "System/Subsystem/TagContainersManager.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"


UBTDecorator_IsActable::UBTDecorator_IsActable()
{
	NodeName = TEXT("IsActable");
}

bool UBTDecorator_IsActable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return false;

	AR1Monster* R1Monster = Cast<AR1Monster>(ControllingPawn);
	if (R1Monster == nullptr) return false;

	if (R1Monster->IsInAnyState(UTagContainersManager::Get(this)->BaseAbilityBlockTgs()) == false)
	{
		return true;
	}
	else
	{
#if 0
		FGameplayTagContainer Container;
		UR1AbilitySystemComponent* ASC = R1Monster->GetR1AbilitySystemComponent();
		ASC->GetOwnedGameplayTags(Container);
		DebugMessage("----------");
		for (const FGameplayTag& Tag : Container)
		{
			DebugMessage(FString::Printf(TEXT("[%s]"), *Tag.ToString()));
		}
#endif

		return false;
	}
}
