

#pragma once

#include "CoreMinimal.h"
#include "Environment/AmbientActor/AmbientActor.h"
#include "Components/TimelineComponent.h"
#include "FlickeringLantern.generated.h"

class UPointLightComponent;

UCLASS()
class PORTFOLIO_API AFlickeringLantern : public AAmbientActor
{
	GENERATED_BODY()
public:
	AFlickeringLantern();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UStaticMeshComponent> LanternMesh;

	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UPointLightComponent> FlickeringLight;

	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UCurveFloat> SwayCurveFloat;

	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UCurveFloat> FlickerCurveFloat;

	UPROPERTY(EditAnywhere, Category = "Config")
	float LightBaseIntensity = 200;

	

protected:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> SwayTimeline;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> FlickerTimeline;

	UFUNCTION()
	void OnSwayUpdate(float Value);

	UFUNCTION()
	void OnFlickerUpdate(float Value);

	UFUNCTION()
	void OnFlickerFinished();

private:
	float PitchRot;
	float YawRot;
	FTimerHandle TimerHandle;
};
