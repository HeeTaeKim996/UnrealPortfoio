


#include "Custom/QuestActor/QuestActorComponent.h"
#include "Suqs.h"
#include "Kismet/GameplayStatics.h"
#include "QuestActorSubsystem.h"

#include "Public/SuqsTaskState.h"

#include "QuestNotifier.h"
#include "SuqsLogger.h"
#include "QuestActorInterface.h"



UQuestActorComponent::UQuestActorComponent()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestActorComponent::BeginPlay()
{
	Super::BeginPlay();

	Register();
}

void UQuestActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Unregister();
}






void UQuestActorComponent::Register()
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TasksRegistered"));

	TArray<const USuqsTaskState*> RelevantTasks;

	for (UQuestNotifier* QuestNotifier : QuestNotifiers)
	{
		
		if (const USuqsTaskState* RelevantTask = QuestNotifier->Initialize_Notifier(this))
		{
			RelevantTasks.Add(RelevantTask);
		}
	}

	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_RegisterInfo RegisterInfo;
		RegisterInfo.RelevantTasks = RelevantTasks;

		QuestActor->QuestActor_OnRegister(RegisterInfo);
	}
}
void UQuestActorComponent::Unregister()
{
	for (UQuestNotifier* QuestNotifier : QuestNotifiers)
	{
		QuestNotifier->OnRemove_Notifier();
	}
}

void UQuestActorComponent::SleepOwner()
{
	if (bIsSleeping == true) return;

	bIsSleeping = true;

	AActor* Owner = GetOwner();

	bWasActorTickEnabled = Owner->IsActorTickEnabled();
	Owner->SetActorTickEnabled(false);
	Owner->SetActorHiddenInGame(true);
	Owner->SetActorEnableCollision(false);

	// TODO : Other Settings
}

void UQuestActorComponent::WakeupOwner()
{
	if (bIsSleeping == false) return;

	bIsSleeping = false;

	AActor* Owner = GetOwner();

	Owner->SetActorTickEnabled(bWasActorTickEnabled);
	Owner->SetActorHiddenInGame(false);
	Owner->SetActorEnableCollision(true);

	// TODO : Other Settings
}









void UQuestActorComponent::OnTaskUpdated(const USuqsTaskState* TaskState)
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TaskUpdated"));


	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_UpdateInfo UpdateInfo;
		UpdateInfo.UpdatedTask = TaskState;

		QuestActor->QuestActor_Update(UpdateInfo);
	}

}
void UQuestActorComponent::OnTaskCompleted(const USuqsTaskState* TaskState)
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TaskCompleted"));

	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_CompleteInfo CompleteInfo;
		CompleteInfo.CompletedTask = TaskState;

		QuestActor->QuestActor_Complete(CompleteInfo);
	}
	
}
void UQuestActorComponent::OnTaskFailed(const USuqsTaskState* TaskState)
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TaskFailed"));

	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_FailInfo FailInfo;
		FailInfo.FailedTask = TaskState;

		QuestActor->QuestActor_Fail(FailInfo);
	}
}



void UQuestActorComponent::OnTaskAdded(const USuqsTaskState* TaskState)
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TaskAdded"));

	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_TaskAddedInfo TaskAddedInfo;
		TaskAddedInfo.AddedTask = TaskState;

		QuestActor->QuestActor_TaskAdded(TaskAddedInfo);
	}
}
void UQuestActorComponent::OnTaskRemoved(const USuqsTaskState* TaskState)
{
	MsgLog(FString("QuestActorComponent.cpp"), FString("TaskRemoved"));

	if (IQuestActorInterface* QuestActor = Cast<IQuestActorInterface>(GetOwner()))
	{
		FQuestActor_TaskRemovedInfo TaskRemovedInfo;
		TaskRemovedInfo.RemovedTask = TaskState;

		QuestActor->QuestActor_TaskRemoved(TaskRemovedInfo);
	}
}





