


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
		SpecHandle = R1Character->ActivateAbility(AbilityTag);
		if (SpecHandle.IsValid() == false)
		{
			return EBTNodeResult::Failed;
		}


		R1Character->GetR1AbilitySystemComponent()->Delegate_OnNotifyAbilityEnded
			.AddDynamic(this, &UBTTaskNode_AsyncAbilityContainer::OnNotifyAbilityEnded);
		

		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTaskNode_AsyncAbilityContainer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	CleanUpDelegate();
}

void UBTTaskNode_AsyncAbilityContainer::OnNotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, 
	bool bWasCancelled)
{
	if (Handle != SpecHandle) return;

	if (WeakOwnerComp.IsValid())
	{
		CleanUpDelegate();

		if (bWasCancelled)
		{
			FinishLatentTask(*WeakOwnerComp.Get(), EBTNodeResult::Failed);
		}
		else
		{
			FinishLatentTask(*WeakOwnerComp.Get(), EBTNodeResult::Succeeded);
		}

		
	}
}



void UBTTaskNode_AsyncAbilityContainer::CleanUpDelegate()
{
	if (WeakOwnerComp.IsValid() == false) return;

	UBehaviorTreeComponent* OwnerComp = WeakOwnerComp.Get();

	AR1Character* R1Character = Cast<AR1Character>(OwnerComp->GetAIOwner()->GetPawn());
	if (R1Character == nullptr) return;

	R1Character->GetR1AbilitySystemComponent()->Delegate_OnNotifyAbilityEnded
		.RemoveDynamic(this, &UBTTaskNode_AsyncAbilityContainer::OnNotifyAbilityEnded);
}
