

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestActorComponent.generated.h"

class USuqsTaskState;
class UQuestNotifier;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUQS_API UQuestActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestActorComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void Register();
	void Unregister();

public:
	void SleepOwner();
	void WakeupOwner();

public:
	bool IsSleeping() { return bIsSleeping; }

	
public:
	void OnTaskUpdated(const USuqsTaskState* TaskState);
	void OnTaskCompleted(const USuqsTaskState* TaskState);
	void OnTaskFailed(const USuqsTaskState* TaskState);
	void OnTaskAdded(const USuqsTaskState* TaskState);
	void OnTaskRemoved(const USuqsTaskState* TaskState);



protected:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Config")
	TArray<TObjectPtr<UQuestNotifier>> QuestNotifiers;

protected:
	bool bIsSleeping;
	bool bWasActorTickEnabled;
};