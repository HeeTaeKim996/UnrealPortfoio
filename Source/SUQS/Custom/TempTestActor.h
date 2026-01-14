

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TempTestActor.generated.h"

class UQuestActorComponent;

UCLASS()
class SUQS_API ATempTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATempTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TObjectPtr<UQuestActorComponent> QuestActorComponent;



protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<UShapeComponent> Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName TaskID;
};
