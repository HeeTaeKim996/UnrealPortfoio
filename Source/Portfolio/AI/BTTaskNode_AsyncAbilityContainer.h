

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AbilitySystem/AbilityCommonStruct.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "BTTaskNode_AsyncAbilityContainer.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTTaskNode_AsyncAbilityContainer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_AsyncAbilityContainer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);

private:
	UFUNCTION()
	void OnNotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled);

private:
	void CleanUpDelegate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag AbilityTag;

	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> WeakOwnerComp;

	FGameplayAbilitySpecHandle SpecHandle;
};
