

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
	UFUNCTION()
	virtual void HandleTraceHit(UMeleeTraceComponent* ThisComponent, AActor* HitActor, const FVector& HitLocation,
		const FVector& HitNormal, FName HitBoneName, FMeleeTraceInstanceHandle TraceHandle, uint8 Protocol);

	UFUNCTION()
	virtual void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	virtual void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMeleeTraceComponent> MeleeTrace;

};
