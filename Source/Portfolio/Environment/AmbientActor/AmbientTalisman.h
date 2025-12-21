

#pragma once

#include "CoreMinimal.h"
#include "Environment/AmbientActor/AmbientActor.h"
#include "Components/TimelineComponent.h"
#include "AmbientTalisman.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AAmbientTalisman : public AAmbientActor
{
	GENERATED_BODY()
public:
	AAmbientTalisman();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UStaticMeshComponent> StaticMesh;


	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UCurveVector> FC_Vector;
	
	UPROPERTY()
	TObjectPtr<UTimelineComponent> RotateTimeline;

protected:
	UFUNCTION()
	void OnTimelineVectorUpdate(FVector Vector);

private:
	FTimerHandle TimerHandle;
};
