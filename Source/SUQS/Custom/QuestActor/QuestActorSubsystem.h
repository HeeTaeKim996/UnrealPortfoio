

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestActorSubsystem.generated.h"

class USuqsProgression;

class UQuestNotifier;

struct FSuqsProgressionEventDetails;
class USuqsTaskState;
class USuqsQuestState;
class USuqsObjectiveState;
struct FSuqsSaveData;


UCLASS()
class SUQS_API UQuestActorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TMap<FName, TArray<UQuestNotifier*>> QuestActorComponentsByQuest;
	TWeakObjectPtr<USuqsProgression> CurrProgression;

public:
	void SetProgression(USuqsProgression* InProg);

	void RegisterQuestActorComponent(UQuestNotifier* QuestActorComponent);
	void UnregisterQuestActorComponent(UQuestNotifier* QuestActorComponent);

	UQuestNotifier* GetQuestActorComponent(const FName& QuestID, const FName& TaskID);

	bool GetQuestActorComponents(const FName& QuestID, const FName& TaskID, TArray<UQuestNotifier*>& OutQuestActorComponents);
	FName GetQuestIdFromTask(USuqsTaskState* Task);
	

protected:
	UFUNCTION()
	void OnProgressionEvent(const FSuqsProgressionEventDetails& Details);
	

	void OnTaskUpdated(USuqsTaskState* Task);
	void OnTaskCompleted(USuqsTaskState* Task);
	void OnTaskFailed(USuqsTaskState* Task);
	void OnTaskAdded(USuqsTaskState* Task);
	void OnTaskRemoved(USuqsTaskState* Task);

protected:
	UFUNCTION()
	void OnObjectiveCompleted(USuqsObjectiveState* Objective);

	UFUNCTION()
	void OnObjectiveFailed(USuqsObjectiveState* Objective);

	UFUNCTION()
	void OnActiveQuestsListChanged();

	UFUNCTION()
	void OnQuestCompleted(USuqsQuestState* Quest);

	UFUNCTION()
	void OnQuestFailed(USuqsQuestState* Quest);

	UFUNCTION()
	void OnQuestAccepted(USuqsQuestState* Quest);

	UFUNCTION()
	void OnProgressionLoaded(USuqsProgression* Progression);

	UFUNCTION()
	void OnProgressParameterProvidersChanged(USuqsProgression* Progression);


	
};
