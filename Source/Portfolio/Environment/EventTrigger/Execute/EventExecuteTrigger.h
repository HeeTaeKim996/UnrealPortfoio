

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Environment/EventTrigger/TriggerInfo.h"
#include "EventExecuteTrigger.generated.h"



UCLASS()
class PORTFOLIO_API AEventExecuteTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AEventExecuteTrigger();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	DECLARE_DELEGATE_OneParam(FDelegate_EventExecuteTrigger,
		const FTriggerInfo& TriggerInfo);
	FDelegate_EventExecuteTrigger Delegate_EventExecuteTrigger;

protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<UShapeComponent> Trigger;
};
