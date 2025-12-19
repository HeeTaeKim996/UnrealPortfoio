

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "MeleeTrace/Public/MeleeTraceComponent.h"
#include "R1Monster.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1Monster : public AR1Character
{
	GENERATED_BODY()
public:
	AR1Monster();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Highlight() override;
	virtual void UnHighlight() override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();


protected:
	virtual bool OnTraceHit(const FMeleeHitInfo& HitInfo) override;
};
