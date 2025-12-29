

#pragma once

#include "CoreMinimal.h"
#include "AI/R1AIController.h"
#include "FieldMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AFieldMonsterController : public AR1AIController
{
	GENERATED_BODY()
public:
	AFieldMonsterController();

public:
	virtual void OnPossess(APawn* InPawn) override;

};
