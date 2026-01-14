

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "TempQuestTrigger.generated.h"

UCLASS()
class SUQS_API ATempQuestTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATempQuestTrigger();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config");
	FGameplayTag QuestID;

protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<UShapeComponent> Trigger;
};
