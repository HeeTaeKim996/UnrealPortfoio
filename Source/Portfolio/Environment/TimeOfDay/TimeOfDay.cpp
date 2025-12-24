


#include "Environment/TimeOfDay/TimeOfDay.h"
#include "Runtime/Engine/Classes/Engine/DirectionalLight.h"
#include "Runtime/Engine/Classes/Engine/SkyLight.h"
#include "Runtime/Engine/Classes/Engine/ExponentialHeightFog.h"
#include "Runtime/Engine/Classes/Engine/PostProcessVolume.h"
#include "Runtime/Engine/Classes/Components/SkyAtmosphereComponent.h"

#include "Runtime/Engine/Classes/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/Classes/Components/SkyLightComponent.h"
#include "Runtime/Engine/Classes/Components/ExponentialHeightFogComponent.h"


const FVector ATimeOfDay::NoonDir = FVector(0, 0, -1);

ATimeOfDay::ATimeOfDay()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATimeOfDay::BeginPlay()
{
	Super::BeginPlay();
	
	ensureAlwaysMsgf(SunLight && SkyLight && HeightFog && SkyAtmosphere,
		TEXT("Time Value Must be assigned"));

	SunLightComponent = SunLight->GetComponent();
	SkyLightComponent = SkyLight->GetLightComponent();
	HeightFogComponent = HeightFog->GetComponent();
	SkyAtmosphereComponent = SkyAtmosphere->GetComponent();


	FVector LightDir = SunLightComponent->GetDirection();
	bool bIsAM = LightDir.X < 0;

	float Cos = NoonDir.Dot(LightDir); // Prelude LightDir is Normalized Vec
	Cos = FMath::Clamp(Cos, -1.f, 1.f);
	float CosAngle = FMath::RadiansToDegrees(acos(Cos));
	float DiffFromNoon = CosAngle / 360.f;

	NormalizedTime = bIsAM ? 0.5f - DiffFromNoon : 0.5f + DiffFromNoon;

	SunRotAxis = bIsAM ? LightDir.Cross(NoonDir) : NoonDir.Cross(LightDir);
	SunRotAxis.Normalize();

	ApplyCurrentTimeSettings();
}

void ATimeOfDay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTickTime)
	{
		TickTime(DeltaTime);
	}
}




void ATimeOfDay::TickTime(float DeltaSeconds)
{
	if (bUseDesiredTime == true)
	{
		NormalizedTime += TimeScale * 50.f * DeltaSeconds;


		float DiffTime = NormalizedTime - DesiredTime;
		if (DiffTime < 0.5f && DiffTime > 0.01f)
		{
			bUseDesiredTime = false;
		}
	}
	else if (bTickTime == true)
	{
		NormalizedTime += TimeScale * DeltaSeconds;
	}

	

	if (NormalizedTime > 1.f)
	{
		NormalizedTime -= 1.f;
	}
	else if (NormalizedTime < 0.f)
	{
		NormalizedTime += 1.f;
	}

	ApplyCurrentTimeSettings();
}

void ATimeOfDay::ApplyCurrentTimeSettings()
{
	UpdateSunRotation();

	//  TODO : Apply Other Settings
}

void ATimeOfDay::UpdateSunRotation()
{
	if (SunLight == nullptr) return;
	
	float Angle = (NormalizedTime - 0.5f) * 360.f;

	FVector NewDirection = NoonDir.RotateAngleAxis(Angle, SunRotAxis);
	SunLight->SetActorRotation(NewDirection.Rotation());
}









void ATimeOfDay::SetTime(float NewTime)
{
	NormalizedTime = FMath::Clamp(NewTime, 0.f, 1.f);

	ApplyCurrentTimeSettings();
}


void ATimeOfDay::SetDesiredTime(float NewDesiredTime)
{
	DesiredTime = FMath::Clamp(NewDesiredTime, 0.f, 24.f);
	bUseDesiredTime = true;
}

