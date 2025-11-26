

#pragma once

#include "CoreMinimal.h"
#include "Character/FieldMonster.h"
#include "FieldMonster_Kronos.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AFieldMonster_Kronos : public AFieldMonster
{
	GENERATED_BODY()
public:
	AFieldMonster_Kronos();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	virtual void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle) override;

	virtual void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle) override;
};
