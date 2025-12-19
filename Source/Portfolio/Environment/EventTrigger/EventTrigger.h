

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventTrigger.generated.h"

USTRUCT()
struct FTriggerInfo
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* TriggeringActor;
	AActor* TriggerOwner;
};



UCLASS()
class PORTFOLIO_API AEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	AEventTrigger();

protected:
	virtual void BeginPlay() override;


protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_EventTrigger,
		const FTriggerInfo&, TriggerInfo);
	FDelegate_EventTrigger Delegate_EventTrigger;

protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<UShapeComponent> Trigger;
};
