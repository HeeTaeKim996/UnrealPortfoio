

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
	void ApplyCurrentTimeSettings();

public:
	UFUNCTION(BlueprintCallable)
	void SetTime(float NewTime);

	UFUNCTION(BlueprintCallable)
	void SetDesiredTime(float NewDesiredTime);

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
	bool bTimePassDefaultly = false;

	UPROPERTY(EditAnywhere, Category = "Config")
	float DefaultTimeScale = 0.001f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float DesiredTimeScale = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Config")
	bool bUseStartTimeSet = false;

	UPROPERTY(EditAnywhere, Category = "Config")
	float StartTime;

	UPROPERTY(EditAnywhere, Category = "Config")
	float SunlightIntensity = 10.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float MoonlightIntensity = 0.05f;

	

protected:
	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ADirectionalLight> DirectionLight;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ASkyLight> SkyLight;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<AExponentialHeightFog> HeightFog;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<ASkyAtmosphere> SkyAtmosphere;

	UPROPERTY(EditInstanceOnly, Category = "World")
	TObjectPtr<APostProcessVolume> PostProcess;

protected:
	UPROPERTY(EditInstanceOnly, Category = "Curves")
	TObjectPtr<UCurveLinearColor> SunColorCurve;

	UPROPERTY(EditInstanceOnly, Category = "Curves")
	TObjectPtr<UCurveFloat> SkyLightIntensityCurve;

	UPROPERTY(EditInstanceOnly, Category = "Curves")
	TObjectPtr<UCurveFloat> FogDensityCurve;

	UPROPERTY(EditInstanceOnly, Category = "Curves")
	TObjectPtr<UCurveLinearColor> FogColorCurve;
	
protected:
	UPROPERTY()
	float NormalizedTime = 0.5f;

	UPROPERTY()
	float DesiredTime;

	UPROPERTY()
	FVector SunRotAxis;

	UPROPERTY()
	TObjectPtr<UDirectionalLightComponent> DirectionalLightComponent;

	UPROPERTY()
	TObjectPtr<USkyLightComponent> SkyLightComponent;

	UPROPERTY()
	TObjectPtr<UExponentialHeightFogComponent> HeightFogComponent;

	UPROPERTY()
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphereComponent;

private:
	static const FVector NoonDir;

	enum EDesiredTimeState : uint8
	{
		None,
		Today,
		Tomorrow,
	};
	EDesiredTimeState DesiredTimeState = EDesiredTimeState::None;
};
