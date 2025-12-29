

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OnNoTarget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTService_OnNoTarget : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_OnNoTarget();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SearchRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActivateTime = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector ActivateTimeKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector OriginalPosKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector IsLeaveWorkableKey;

private:
	double CachedSearchRadiusSquared;
};
