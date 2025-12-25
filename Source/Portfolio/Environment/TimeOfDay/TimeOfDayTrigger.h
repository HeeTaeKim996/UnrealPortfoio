

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeOfDayTrigger.generated.h"

class ATimeOfDay;

UCLASS()
class PORTFOLIO_API ATimeOfDayTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimeOfDayTrigger();

protected:
	virtual void BeginPlay() override;


protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DesiredTime;

protected:
	UPROPERTY()
	TWeakObjectPtr<ATimeOfDay> TimeOfDay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UShapeComponent> Trigger;
};
