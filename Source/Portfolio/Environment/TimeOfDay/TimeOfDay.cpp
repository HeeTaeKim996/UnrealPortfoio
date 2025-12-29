


#include "Environment/TimeOfDay/TimeOfDay.h"
#include "Runtime/Engine/Classes/Engine/DirectionalLight.h"
#include "Runtime/Engine/Classes/Engine/SkyLight.h"
#include "Runtime/Engine/Classes/Engine/ExponentialHeightFog.h"
#include "Runtime/Engine/Classes/Engine/PostProcessVolume.h"
#include "Runtime/Engine/Classes/Components/SkyAtmosphereComponent.h"

#include "Runtime/Engine/Classes/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/Classes/Components/SkyLightComponent.h"
#include "Runtime/Engine/Classes/Components/ExponentialHeightFogComponent.h"
#include "Curves/CurveLinearColor.h"

const FVector ATimeOfDay::NoonDir = FVector(0, 0, -1);

ATimeOfDay::ATimeOfDay()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATimeOfDay::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(DirectionLight && SkyLight && HeightFog && SkyAtmosphere,
		TEXT("Time Value Must be assigned"));

	DirectionalLightComponent = Cast<UDirectionalLightComponent>(DirectionLight->GetLightComponent());
	SkyLightComponent = SkyLight->GetLightComponent();
	HeightFogComponent = HeightFog->GetComponent();
	SkyAtmosphereComponent = SkyAtmosphere->GetComponent();


	FVector LightDir = DirectionalLightComponent->GetDirection();
	bool bIsAM = LightDir.X < 0;

	float Cos = NoonDir.Dot(LightDir); // Prelude LightDir is Normalized Vec
	Cos = FMath::Clamp(Cos, -1.f, 1.f);
	float CosAngle = FMath::RadiansToDegrees(acos(Cos));
	float DiffFromNoon = CosAngle / 360.f;

	NormalizedTime = bIsAM ? 0.5f - DiffFromNoon : 0.5f + DiffFromNoon;

	SunRotAxis = bIsAM ? LightDir.Cross(NoonDir) : NoonDir.Cross(LightDir);
	SunRotAxis.Normalize();


	if (bUseStartTimeSet)
	{
		NormalizedTime = StartTime;
		NormalizedTime = FMath::Clamp(NormalizedTime, 0.f, 1.f);
	}

	ApplyCurrentTimeSettings();
}

void ATimeOfDay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DesiredTimeState != EDesiredTimeState::None)
	{
		NormalizedTime += DesiredTimeScale * DeltaTime;

		if (DesiredTimeState == EDesiredTimeState::Tomorrow && NormalizedTime > 1.f)
		{
			DesiredTimeState = EDesiredTimeState::Today;
			NormalizedTime -= 1.f;
		}
		else if (DesiredTimeState == EDesiredTimeState::Today && NormalizedTime >= DesiredTime)
		{
			DesiredTimeState = EDesiredTimeState::None;
			NormalizedTime = DesiredTime;
		}

		if (NormalizedTime > 1.f)
		{
			NormalizedTime -= 1.f;
		}

		ApplyCurrentTimeSettings();
	}
	else if (bTimePassDefaultly == true)
	{
		NormalizedTime += DefaultTimeScale * DeltaTime;

		if (NormalizedTime > 1.f)
		{
			NormalizedTime -= 1.f;
		}

		ApplyCurrentTimeSettings();
	}
}




void ATimeOfDay::ApplyCurrentTimeSettings()
{
	// Set DirectionLight Rotation
	if (DirectionLight) 
	{
		if (NormalizedTime >= 0.25f && NormalizedTime <= 0.75f)
		{
			float Angle = (NormalizedTime - 0.5f) * 360.f;

			FVector NewDirection = NoonDir.RotateAngleAxis(Angle, SunRotAxis);
			DirectionLight->SetActorRotation(NewDirection.Rotation());
		}
		else
		{
			FVector NewDirection = NoonDir.RotateAngleAxis(0.4f, SunRotAxis);
			DirectionLight->SetActorRotation(NewDirection.Rotation());
		}
	}


	// Set Directional Light's Intensity and Color
	if (DirectionalLightComponent)
	{
		if (NormalizedTime >= 0.25f && NormalizedTime <= 0.75f)
		{
			if (DirectionalLightComponent->Intensity != SunlightIntensity)
			{
				DirectionalLightComponent->SetIntensity(SunlightIntensity);
			}
		}
		else
		{
			if (DirectionalLightComponent->Intensity != MoonlightIntensity)
			{
				DirectionalLightComponent->SetIntensity(MoonlightIntensity);
			}
		}
		if (SunColorCurve)
		{
			DirectionalLightComponent->SetLightColor(SunColorCurve->GetLinearColorValue(NormalizedTime));
		}
	}
	
	// Set SkyLight's Intensity
	if (SkyLight)
	{
		if (SkyLightIntensityCurve)
		{
			SkyLightComponent->SetIntensity(SkyLightIntensityCurve->GetFloatValue(NormalizedTime));
		}


		SkyLightComponent->RecaptureSky();
	}

	// Set Fog 
	if (HeightFogComponent)
	{
		if (FogDensityCurve)
		{
			HeightFogComponent->SetFogDensity(FogDensityCurve->GetFloatValue(NormalizedTime));
		}
		
		if (FogColorCurve)
		{
			HeightFogComponent->SetFogInscatteringColor(FogColorCurve->GetLinearColorValue(NormalizedTime));
		}
	}
}










void ATimeOfDay::SetTime(float NewTime)
{
	NormalizedTime = FMath::Clamp(NewTime, 0.f, 1.f);

	ApplyCurrentTimeSettings();
}


void ATimeOfDay::SetDesiredTime(float NewDesiredTime)
{
	DesiredTime = FMath::Clamp(NewDesiredTime, 0.f, 1.f);

	if (FMath::Abs(NewDesiredTime - NormalizedTime) < 0.005f)
	{
		NormalizedTime = DesiredTime;
		ApplyCurrentTimeSettings();
		return;
	}

	if (NewDesiredTime > NormalizedTime)
	{
		DesiredTimeState = EDesiredTimeState::Today;
	}
	else if (NewDesiredTime < NormalizedTime)
	{
		DesiredTimeState = EDesiredTimeState::Tomorrow;
	}
}

