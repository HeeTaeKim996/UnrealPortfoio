


#include "Custom/QuestActor/QuestActorSubsystem.h"
#include "Public/SuqsProgression.h"
#include "QuestActorComponent.h"
#include "QuestNotifier.h"



void UQuestActorSubsystem::SetProgression(USuqsProgression* InProg)
{
	if (CurrProgression.IsValid())
	{
		CurrProgression->OnProgressionEvent.RemoveDynamic(this, &UQuestActorSubsystem::OnProgressionEvent);
		CurrProgression->OnObjectiveCompleted.RemoveDynamic(this, &UQuestActorSubsystem::OnObjectiveCompleted);
		CurrProgression->OnObjectiveFailed.RemoveDynamic(this, &UQuestActorSubsystem::OnObjectiveFailed);
		CurrProgression->OnActiveQuestsListChanged.RemoveDynamic(this, &UQuestActorSubsystem::OnActiveQuestsListChanged);
		CurrProgression->OnQuestCompleted.RemoveDynamic(this, &UQuestActorSubsystem::OnQuestCompleted);
		CurrProgression->OnQuestAccepted.RemoveDynamic(this, &UQuestActorSubsystem::OnQuestAccepted);
		CurrProgression->OnProgressionLoaded.RemoveDynamic(this, &UQuestActorSubsystem::OnProgressionLoaded);
		CurrProgression->OnParameterProvidersChanged.RemoveDynamic(this, &UQuestActorSubsystem::OnProgressParameterProvidersChanged);
	}

	CurrProgression = InProg;

	if (IsValid(InProg))
	{
		CurrProgression->OnProgressionEvent.AddDynamic(this, &UQuestActorSubsystem::OnProgressionEvent);
		CurrProgression->OnObjectiveCompleted.AddDynamic(this, &UQuestActorSubsystem::OnObjectiveCompleted);
		CurrProgression->OnObjectiveFailed.AddDynamic(this, &UQuestActorSubsystem::OnObjectiveFailed);
		CurrProgression->OnActiveQuestsListChanged.AddDynamic(this, &UQuestActorSubsystem::OnActiveQuestsListChanged);
		CurrProgression->OnQuestCompleted.AddDynamic(this, &UQuestActorSubsystem::OnQuestCompleted);
		CurrProgression->OnQuestAccepted.AddDynamic(this, &UQuestActorSubsystem::OnQuestAccepted);
		CurrProgression->OnProgressionLoaded.AddDynamic(this, &UQuestActorSubsystem::OnProgressionLoaded);
		CurrProgression->OnParameterProvidersChanged.AddDynamic(this, &UQuestActorSubsystem::OnProgressParameterProvidersChanged);
	}
}

void UQuestActorSubsystem::RegisterQuestActorComponent(UQuestNotifier* QuestActorComponent)
{


	bool bInserted = false;

	const FGameplayTag QuestID = QuestActorComponent->GetQuestID();
	const FGameplayTag TaskID = QuestActorComponent->GetTaskID();

	TArray<UQuestNotifier*>& List = QuestActorComponentsByQuest.FindOrAdd(QuestID);

	for (int i = 0; i < List.Num(); i++)
	{
		const UQuestNotifier* Curr = List[i];

		if (Curr == QuestActorComponent)
		{
			bInserted = true;
			break;
		}


		if (Curr->GetTaskID() == TaskID)
		{
			List.Insert(QuestActorComponent, i);
			bInserted = true;
			break;
		}
	}

	if (bInserted == false)
	{
		List.Add(QuestActorComponent);
		bInserted = true;
	}


	if (CurrProgression.IsValid())
	{
		bool IsTaskRelevant = CurrProgression->IsTaskRelevant(QuestID, TaskID);
		if (IsTaskRelevant)
		{
			QuestActorComponent->SetIsRelevant(true, CurrProgression->GetTaskState(QuestID, TaskID));
		}
		QuestActorComponent->SetIsRelevant(false, nullptr);
	}

}

void UQuestActorSubsystem::UnregisterQuestActorComponent(UQuestNotifier* QuestActorComponent)
{
	TArray<UQuestNotifier*>* const pList = QuestActorComponentsByQuest.Find(QuestActorComponent->GetQuestID());
	if (pList)
	{
		pList->RemoveSingle(QuestActorComponent);
	}

}

UQuestNotifier* UQuestActorSubsystem::GetQuestActorComponent(const FGameplayTag& QuestID, const FGameplayTag& TaskID)
{
	TArray<UQuestNotifier*>* const pList = QuestActorComponentsByQuest.Find(QuestID);
	if (pList)
	{
		for (UQuestNotifier* C : *pList)
		{
			if (C->GetTaskID() == TaskID)
			{
				return C;
			}
		}
	}
	return nullptr;
}

bool UQuestActorSubsystem::GetQuestActorComponents(const FGameplayTag& QuestID, const FGameplayTag& TaskID, 
	TArray<UQuestNotifier*>& OutQuestActorComponents)
{
	OutQuestActorComponents.Empty();

	TArray<UQuestNotifier*>* const pList = QuestActorComponentsByQuest.Find(QuestID);
	bool bAnyFound = false;
	if (pList)
	{
		bool bFoundTask = false;
		for (UQuestNotifier* C : *pList)
		{
			if (C->GetTaskID() == TaskID)
			{
				bFoundTask = true;
				bAnyFound = true;

				OutQuestActorComponents.Add(C);
			}
			else if (bFoundTask)
			{
				break;
			}
		}
	}
	return bAnyFound;
}

FGameplayTag UQuestActorSubsystem::GetQuestIdFromTask(USuqsTaskState* Task)
{
	if (USuqsObjectiveState* Objective = Task->GetParentObjective())
	{
		if (USuqsQuestState* Quest = Objective->GetParentQuest())
		{
			return Quest->GetIdentifier();
		}
	}

	return FGameplayTag::EmptyTag;
}













void UQuestActorSubsystem::OnProgressionEvent(const FSuqsProgressionEventDetails& Details)
{
	if (Details.EventType == ESuqsProgressionEventType::TaskUpdated)
	{
		OnTaskUpdated(Details.Task);
	}
	else if (Details.EventType == ESuqsProgressionEventType::TaskCompleted)
	{
		OnTaskCompleted(Details.Task);
	}
	else if (Details.EventType == ESuqsProgressionEventType::TaskAdded)
	{
		OnTaskAdded(Details.Task);
	}
	else if (Details.EventType == ESuqsProgressionEventType::TaskRemoved)
	{
		OnTaskRemoved(Details.Task);
	}
	else if (Details.EventType == ESuqsProgressionEventType::TaskFailed)
	{
		OnTaskFailed(Details.Task);
	}
}

void UQuestActorSubsystem::OnTaskUpdated(USuqsTaskState* Task)
{
	TArray<UQuestNotifier*> QuestActorComponents;
	if (GetQuestActorComponents(GetQuestIdFromTask(Task), Task->GetIdentifier(), QuestActorComponents))
	{
		for (UQuestNotifier* QC : QuestActorComponents)
		{
			QC->OnTaskUpdated(Task);
		}
	}
}

void UQuestActorSubsystem::OnTaskCompleted(USuqsTaskState* Task)
{
	TArray<UQuestNotifier*> QuestActorComponents;
	if (GetQuestActorComponents(GetQuestIdFromTask(Task), Task->GetIdentifier(), QuestActorComponents))
	{
		for (UQuestNotifier* QC : QuestActorComponents)
		{
			QC->OnTaskCompleted(Task);
		}
	}
}

void UQuestActorSubsystem::OnTaskFailed(USuqsTaskState* Task)
{
	TArray<UQuestNotifier*> QuestActorComponents;
	if (GetQuestActorComponents(GetQuestIdFromTask(Task), Task->GetIdentifier(), QuestActorComponents))
	{
		for (UQuestNotifier* QC : QuestActorComponents)
		{
			QC->OnTaskFailed(Task);
		}
	}
}

void UQuestActorSubsystem::OnTaskAdded(USuqsTaskState* Task)
{
	TArray<UQuestNotifier*> QuestActorComponents;
	if (GetQuestActorComponents(GetQuestIdFromTask(Task), Task->GetIdentifier(), QuestActorComponents))
	{
		for (UQuestNotifier* QC : QuestActorComponents)
		{
			QC->OnTaskAdded(Task);
		}
	}
}

void UQuestActorSubsystem::OnTaskRemoved(USuqsTaskState* Task)
{
	TArray<UQuestNotifier*> QuestActorComponents;
	if (GetQuestActorComponents(GetQuestIdFromTask(Task), Task->GetIdentifier(), QuestActorComponents))
	{
		for (UQuestNotifier* QC : QuestActorComponents)
		{
			QC->OnTaskRemoved(Task);
		}
	}
}
















void UQuestActorSubsystem::OnObjectiveCompleted(USuqsObjectiveState* Objective)
{
}

void UQuestActorSubsystem::OnObjectiveFailed(USuqsObjectiveState* Objective)
{
}

void UQuestActorSubsystem::OnActiveQuestsListChanged()
{

}

void UQuestActorSubsystem::OnQuestCompleted(USuqsQuestState* Quest)
{
}

void UQuestActorSubsystem::OnQuestFailed(USuqsQuestState* Quest)
{
}


void UQuestActorSubsystem::OnQuestAccepted(USuqsQuestState* Quest)
{

}

void UQuestActorSubsystem::OnProgressionLoaded(USuqsProgression* Progression)
{

}

void UQuestActorSubsystem::OnProgressParameterProvidersChanged(USuqsProgression* Progression)
{

}

