

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeOfDay.generated.h"

class ADirectionalLight;
class ASkyLight;
class AExponentialHeightFog;
class APostProcessVolume;
class ASkyAtmosphere;

class UDirectionalLightComponent;
class USkyLightComponent;
class UExponentialHeightFogComponent;
class USkyAtmosphereComponent;


UCLASS()
class PORTFOLIO_API ATimeOfDay : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimeOfDay();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void TickTime(float DeltaSeconds);
	void ApplyCurrentTimeSettings();
	void UpdateSunRotation();

public:
	UFUNCTION(BlueprintCallable)
	void SetTime(float NewTime);

	UFUNCTION(BlueprintCallable)
	void SetDesiredTime(float NewDesiredTime);

protected:

	UPROPERTY(EditAnywhere, Category = "Time")
	float TimeScale = 0.001f;

	UPROPERTY(EditAnywhere, Category = "Time")
	bool bTickTime = true;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ADirectionalLight> SunLight;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ASkyLight> SkyLight;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<AExponentialHeightFog> HeightFog;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<APostProcessVolume> PostProcess;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ASkyAtmosphere> SkyAtmosphere;

protected:
	UPROPERTY()
	float NormalizedTime = 0.5f;

	UPROPERTY()
	float DesiredTime;

	UPROPERTY()
	FVector SunRotAxis;

	UPROPERTY()
	TObjectPtr<UDirectionalLightComponent> SunLightComponent;

	UPROPERTY()
	TObjectPtr<USkyLightComponent> SkyLightComponent;

	UPROPERTY()
	TObjectPtr<UExponentialHeightFogComponent> HeightFogComponent;

	UPROPERTY()
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphereComponent;

private:
	static const FVector NoonDir;
	bool bUseDesiredTime = false;
};
