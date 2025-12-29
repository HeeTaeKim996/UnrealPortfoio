

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamingTrigger.generated.h"



UCLASS()
class PORTFOLIO_API ALevelStreamingTrigger : public AActor
{
	GENERATED_BODY()

public:
	ALevelStreamingTrigger();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);


protected:
	UPROPERTY(EditInstanceOnly, Category = "Config")
	TSoftObjectPtr<UWorld> LevelAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShapeComponent")
	TObjectPtr<UShapeComponent> Trigger;
};
