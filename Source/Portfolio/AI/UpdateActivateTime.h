

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UpdateActivateTime.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UUpdateActivateTime : public UBTService
{
	GENERATED_BODY()
public:
	UUpdateActivateTime();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector ActivateTimeKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetKey;
};
