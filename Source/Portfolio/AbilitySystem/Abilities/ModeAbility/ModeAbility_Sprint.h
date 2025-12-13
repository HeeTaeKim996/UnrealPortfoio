

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ModeAbility/ModeAbility.h"
#include "ModeAbility_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UModeAbility_Sprint : public UModeAbility
{
	GENERATED_BODY()
public:
	UModeAbility_Sprint();

public:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
