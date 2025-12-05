

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsActable.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTDecorator_IsActable : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsActable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
