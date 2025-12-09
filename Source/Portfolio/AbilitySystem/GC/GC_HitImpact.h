

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_HitImpact.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGC_HitImpact : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UGC_HitImpact();

public:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
		const FGameplayCueParameters& Parameters) override;
};
