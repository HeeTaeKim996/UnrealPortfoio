

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "R1AIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AR1AIController();

	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIComponents")
	TObjectPtr<class UBlackboardData> BlackboardAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIComponents")
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;
};
