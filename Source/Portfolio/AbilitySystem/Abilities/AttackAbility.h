

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionAbility.h"
#include "AttackAbility.generated.h"



struct FMeleeHitInfo;

UCLASS()
class PORTFOLIO_API UAttackAbilityTask : public UActionAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	UFUNCTION()
	virtual void OnTraceHit(FMeleeHitInfo MeleeHitInfo);
};



UCLASS()
class PORTFOLIO_API UAttackAbility : public UActionAbility
{
	GENERATED_BODY()
	
};
