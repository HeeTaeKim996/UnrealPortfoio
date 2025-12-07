


#include "AI/BTTaskNode_AsyncAbilityContainer.h"
#include "Character/R1Character.h"
#include "AIController.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"

UBTTaskNode_AsyncAbilityContainer::UBTTaskNode_AsyncAbilityContainer()
	: Super()
{

}

EBTNodeResult::Type UBTTaskNode_AsyncAbilityContainer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	WeakOwnerComp = &OwnerComp;
	AR1Character* R1Character = Cast<AR1Character>(OwnerComp.GetAIOwner()->GetPawn());



	if (R1Character)
	{
		if (R1Character->ActivateAbility(AbilityTag) == false)
		{
			return EBTNodeResult::Failed;
		}


		R1Character->GAS_OnAbilitySucceed.AddDynamic(this, &UBTTaskNode_AsyncAbilityContainer::OnAbilitySucceed);

		

		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTaskNode_AsyncAbilityContainer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	CleanUpDelegate();
}


void UBTTaskNode_AsyncAbilityContainer::OnAbilityCancel(FAbilityCancelInfo CancelInfo)
{
	for (FGameplayTag AbilityCancelTag : CancelInfo.AbilityCancelTags)
	{
		if (AbilityTag.MatchesTag(AbilityCancelTag))
		{
			if (WeakOwnerComp.IsValid())
			{
				CleanUpDelegate();
				FinishLatentTask(*WeakOwnerComp.Get(), EBTNodeResult::Failed);
			}
			return;
		}
	}
}

void UBTTaskNode_AsyncAbilityContainer::OnAbilitySucceed(FAbilitySucceedInfo SucceedInfo)
{
	for (FGameplayTag AbilityCancelTag : SucceedInfo.AbilitySucceedTags)
	{
		if (AbilityCancelTag.MatchesTag(AbilityTag))
		{
			if (WeakOwnerComp.IsValid())
			{
				CleanUpDelegate();
				FinishLatentTask(*WeakOwnerComp.Get(), EBTNodeResult::Succeeded);
			}
			return;
		}
	}
}

void UBTTaskNode_AsyncAbilityContainer::CleanUpDelegate()
{
	if (WeakOwnerComp.IsValid() == false) return;

	UBehaviorTreeComponent* OwnerComp = WeakOwnerComp.Get();

	AR1Character* R1Character = Cast<AR1Character>(OwnerComp->GetAIOwner()->GetPawn());
	if (R1Character == nullptr) return;

	R1Character->GAS_OnAbilitySucceed.RemoveDynamic(this, &UBTTaskNode_AsyncAbilityContainer::OnAbilitySucceed);
}
