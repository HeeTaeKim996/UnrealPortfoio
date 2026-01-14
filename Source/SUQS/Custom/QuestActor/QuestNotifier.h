

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestNotifier.generated.h"

class USuqsTaskState;
class UQuestActorComponent;

// ¡Ø EditInlineNew		: Instanced when in editor bp' + inputed
// ¡Ø DefaultToInstanced	: Outer is Owner
UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType)
class SUQS_API UQuestNotifier : public UObject
{
	GENERATED_BODY()
public:
	UQuestNotifier();

public:
	void Initialize_Notifier(UQuestActorComponent* InParent);
	void OnRemove_Notifier();

private:
	void Register();
	void UnRegister();

public:
	bool IsNotifierRelevant() { return bIsRelevant; }



public:
	void SetIsRelevant(bool bNewIsRelevant, const USuqsTaskState* Task);
	FName GetQuestID() const { return QuestID; }
	FName GetTaskID() const { return TaskID; }




public:
	void OnTaskUpdated(const USuqsTaskState* TaskState);
	void OnTaskCompleted(const USuqsTaskState* TaskState);
	void OnTaskFailed(const USuqsTaskState* TaskState);
	void OnTaskAdded(const USuqsTaskState* TaskState);
	void OnTaskRemoved(const USuqsTaskState* TaskState);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName TaskID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	uint8 TempSequenceIndex = 0;



protected:
	UPROPERTY()
	TObjectPtr<UQuestActorComponent> ParentComponent;

	bool bIsRelevant = false;
	bool bIsRegistered = false;
};
