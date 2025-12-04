

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_HitReaction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = "GameplayCueNotify")
class PORTFOLIO_API UGC_HitReaction : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UGC_HitReaction();

public:

	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, 
		const FGameplayCueParameters& Parameters) override;
};
