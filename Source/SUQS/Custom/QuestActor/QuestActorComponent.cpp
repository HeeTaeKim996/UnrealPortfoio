


#include "Custom/QuestActor/QuestActorComponent.h"
#include "Suqs.h"
#include "Kismet/GameplayStatics.h"
#include "QuestActorSubsystem.h"

#include "Public/SuqsTaskState.h"

#include "QuestNotifier.h"
#include "SuqsLogger.h"
													\



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
	bool bIsAnyRelevant = false;
	for (UQuestNotifier* QuestNotifier : QuestNotifiers)
	{
		QuestNotifier->Initialize_Notifier(this);
		if (QuestNotifier->IsNotifierRelevant() == true)
		{
			bIsAnyRelevant = true;
		}
	}

	if (bIsAnyRelevant == false)
	{
		SleepOwner();
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
	MsgBoth(FString("QuestActorComponent.cpp"), FString("TaskUpdated"));
}
void UQuestActorComponent::OnTaskCompleted(const USuqsTaskState* TaskState)
{
	MsgBoth(FString("QuestActorComponent.cpp"), FString("TaskCompleted"));
}
void UQuestActorComponent::OnTaskFailed(const USuqsTaskState* TaskState)
{
	MsgBoth(FString("QuestActorComponent.cpp"), FString("TaskFailed"));
}

void UQuestActorComponent::OnTaskAdded(const USuqsTaskState* TaskState)
{
	MsgBoth(FString("QuestActorComponent.cpp"), FString("TaskAdded"));

	WakeupOwner();
}
void UQuestActorComponent::OnTaskRemoved(const USuqsTaskState* TaskState)
{
	MsgBoth(FString("QuestActorComponent.cpp"), FString("TaskRemoved"));
}





