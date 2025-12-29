

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_AmbientCrow.generated.h"

class AAmbientCrow;

UCLASS()
class PORTFOLIO_API AAI_AmbientCrow : public AAIController
{
	GENERATED_BODY()
public:
	AAI_AmbientCrow();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void EndPlay(const EEndPlayReason::Type EndReason) override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID,
		const FPathFollowingResult& Result) override;	

private:
	void DoRoam();

public:
	void StartFly();


protected:
	FVector FlyingDir = FVector(0, 1, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float RoamRadius = 15.f;

private:
	TObjectPtr<AAmbientCrow> Crow;

	FTimerHandle CrowTimerHandle;

	FVector StartPos;
	bool IsFlying = false;
	FVector RoamAimPos;

private:
	

	bool bIsFlying = false;
	float FlyElapsed = 0.f;
	float HeightUp = 0.f;

};
