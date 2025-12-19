

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Kronos_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTTaskNode_Kronos_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_Kronos_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);


private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* EndMontage, bool bInterruped);

	bool bMontageEnded;

public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetPlayer;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TObjectPtr<class UAnimMontage> AttackMontage = nullptr;

};
