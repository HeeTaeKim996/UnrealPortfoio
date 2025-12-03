

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "MonsterBB.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UMonsterBB : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
public:
	UMonsterBB();

public:
	UPROPERTY(EditAnywhere, Category = "Monster")
	TObjectPtr<class AR1Character> TargetCharacter;
};
