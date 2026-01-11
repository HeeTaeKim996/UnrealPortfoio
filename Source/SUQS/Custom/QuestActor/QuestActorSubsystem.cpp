


#include "Custom/QuestActor/QuestActorSubsystem.h"
#include "Public/SuqsProgression.h"
#include "QuestActorComponent.h"


void UQuestActorSubsystem ::SetProgression(USuqsProgression* InProg)
{
	if (Progression.IsValid())
	{
		// TODO : Unregister Delegates
	}

	Progression = InProg;

	if (IsValid(InProg))
	{
		// TODO Register Delegates
	}
}

void UQuestActorSubsystem::RegisterQuestActorComponent(UQuestActorComponent* QuestActorComponent)
{
	TArray<UQuestActorComponent*>& List = QuestActorComponentsByQuest.FindOrAdd(QuestActorComponent->GetQuestID());

	bool bInserted = false;
	bool bExistingTask = false;

	for (int i = 0; i < List.Num(); i++)
	{
		const UQuestActorComponent* Curr = List[i];

		if (Curr == QuestActorComponent)
		{
			bInserted = true;
		}

		if (Curr->GetTaskID() == QuestActorComponent->GetTaskID())
		{
			bExistingTask = true;
		}

		if (bExistingTask &&
			(Curr->GetSequenceIndex() > QuestActorComponent->GetSequenceIndex() || Curr->GetTaskID() != QuestActorComponent->GetTaskID())
			)
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

	if (bInserted)
	{
		if (Progression.IsValid())
		{
			QuestActorComponent->SetIsCurrent(Progression->IsTaskRelevant(QuestActorComponent->GetQuestID(), QuestActorComponent->GetTaskID()));
		}
	}
}

void UQuestActorSubsystem::UnregisterQuestActorComponent(UQuestActorComponent* QuestActorComponent)
{
	TArray<UQuestActorComponent*>* const pList = QuestActorComponentsByQuest.Find(QuestActorComponent->GetQuestID());
	if (pList)
	{
		pList->RemoveSingle(QuestActorComponent);
	}

}

UQuestActorComponent* UQuestActorSubsystem::GetQuestActorComponent(const FName& QuestID, const FName& TaskID, bool bOnlyEnabled)
{
	TArray<UQuestActorComponent*>* const pList = QuestActorComponentsByQuest.Find(QuestID);
	if (pList)
	{
		for (UQuestActorComponent* C : *pList)
		{
			if (C->GetTaskID() == TaskID &&
				(bOnlyEnabled == false || C->IsQuesetComponentActive())
				)
			{
				return C;
			}
		}
	}
	return nullptr;
}

bool UQuestActorSubsystem::GetQuestActorComponents(const FName& QuestID, const FName& TaskID, bool bOnlyEnabled, TArray<UQuestActorComponent*>& OutQuestActorComponents)
{
	OutQuestActorComponents.Empty();

	TArray<UQuestActorComponent*>* const pList = QuestActorComponentsByQuest.Find(QuestID);
	bool bAnyFound = false;
	if (pList)
	{
		bool bFoundTask = false;
		for (UQuestActorComponent* C : *pList)
		{
			if (C->GetTaskID() == TaskID)
			{
				bFoundTask = true;
				if (bOnlyEnabled == false || C->IsQuesetComponentActive())
				{
					OutQuestActorComponents.Add(C);
					bAnyFound = true;
				}
			}
			else if (bFoundTask)
			{
				break;
			}
		}
	}
	return bAnyFound;
}
