

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_Die.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGameplayCueNotify_Die : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UGameplayCueNotify_Die();

public:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
		const FGameplayCueParameters& Parameters) override;
};
