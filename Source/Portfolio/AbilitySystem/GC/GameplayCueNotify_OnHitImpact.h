

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_OnHitImpact.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGameplayCueNotify_OnHitImpact : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UGameplayCueNotify_OnHitImpact();
public:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
		const FGameplayCueParameters& Parameters) override;
};
