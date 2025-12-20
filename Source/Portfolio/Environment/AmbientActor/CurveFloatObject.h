

#pragma once

#include "CoreMinimal.h"
#include "Environment/AmbientActor/AmbientActor.h"
#include "Components/TimelineComponent.h"
#include "CurveFloatObject.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ACurveFloatObject : public AAmbientActor
{
	GENERATED_BODY()
public:
	ACurveFloatObject();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Box;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	TObjectPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	float CurveSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	float CurveIntensity = 1.f;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	bool bUseRollRot = false;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	bool bUsePitchRot = false;

	UPROPERTY(EditAnywhere, Category = "CurveConfig")
	bool bUseYawRot = false;


	UFUNCTION()
	void OnCurveTimeUpdate(float Value);


};
