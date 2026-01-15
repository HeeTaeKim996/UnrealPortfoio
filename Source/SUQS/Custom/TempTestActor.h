

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "QuestActor/QuestActorInterface.h"
#include "TempTestActor.generated.h"

class UQuestActorComponent;

UCLASS()
class SUQS_API ATempTestActor : public AActor, public IQuestActorInterface
{
	GENERATED_BODY()
	
public:	
	ATempTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:
	virtual void QuestActor_OnRegister(const FQuestActor_RegisterInfo& BeginPlayInfo) override;
	virtual void QuestActor_Update(const FQuestActor_UpdateInfo& UpdateInfo) override;
	virtual void QuestActor_Complete(const FQuestActor_CompleteInfo& CompleteInfo) override;
	virtual void QuestActor_Fail(const FQuestActor_FailInfo& FailInfo) override;
	virtual void QuestActor_TaskAdded(const FQuestActor_TaskAddedInfo& TaskAddedInfo) override;
	virtual void QuestActor_TaskRemoved(const FQuestActor_TaskRemovedInfo& RegisterInfo) override;



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
	FGameplayTag QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FGameplayTag TaskID;
};
