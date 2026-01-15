

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestActorInterface.generated.h"


class USuqsTaskState;


USTRUCT()
struct FQuestActor_RegisterInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<const USuqsTaskState*> RelevantTasks;
};

USTRUCT()
struct FQuestActor_UpdateInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const USuqsTaskState* UpdatedTask;
};

USTRUCT()
struct FQuestActor_CompleteInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const USuqsTaskState* CompletedTask;
};

USTRUCT()
struct FQuestActor_FailInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const USuqsTaskState* FailedTask;
};

USTRUCT()
struct FQuestActor_TaskAddedInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const USuqsTaskState* AddedTask;
};

USTRUCT()
struct FQuestActor_TaskRemovedInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const USuqsTaskState* RemovedTask;
};













// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestActorInterface : public UInterface
{
	GENERATED_BODY()
};


class SUQS_API IQuestActorInterface
{
	GENERATED_BODY()


public:
	virtual void QuestActor_OnRegister(const FQuestActor_RegisterInfo& RegisterInfo) = 0;
	virtual void QuestActor_Update(const FQuestActor_UpdateInfo& UpdateInfo) = 0;
	virtual void QuestActor_Complete(const FQuestActor_CompleteInfo& CompleteInfo) = 0;
	virtual void QuestActor_Fail(const FQuestActor_FailInfo& FailInfo) = 0;
	virtual void QuestActor_TaskAdded(const FQuestActor_TaskAddedInfo& TaskAddedInfo) = 0;
	virtual void QuestActor_TaskRemoved(const FQuestActor_TaskRemovedInfo& TaskRemovedInfo) = 0;

};
