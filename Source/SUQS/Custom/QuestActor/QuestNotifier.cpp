


#include "Custom/QuestActor/QuestNotifier.h"
#include "QuestActorSubsystem.h"
#include "Suqs.h"
#include "QuestActorComponent.h"

#define TempMessage(x)												\
do {																\
	if (GEngine)													\
	{																\
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, x); \
	}																\
	UE_LOG(LogSUQS, Warning, TEXT("%s"), x);						\
} while (0)		


UQuestNotifier::UQuestNotifier()
	: Super()
{
	
}

void UQuestNotifier::Initialize_Notifier(UQuestActorComponent* InParent)
{
	ParentComponent = InParent;
	Register();
}

void UQuestNotifier::OnRemove_Notifier()
{
	UnRegister();
}

void UQuestNotifier::Register()
{
	if (bIsRegistered == true) return;

	const UGameInstance* GI = GetWorld()->GetGameInstance();
	if (GI == nullptr) return;

	UQuestActorSubsystem* QuestActorSubsystem = GI->GetSubsystem<UQuestActorSubsystem>();
	if (QuestActorSubsystem == nullptr) return;

	QuestActorSubsystem->RegisterQuestActorComponent(this);

}
void UQuestNotifier::UnRegister()
{
	if (bIsRegistered == true) return;

	const UGameInstance* GI = GetWorld()->GetGameInstance();
	if (GI == nullptr) return;

	UQuestActorSubsystem* QuestActorSubsystem = GI->GetSubsystem<UQuestActorSubsystem>();
	if (QuestActorSubsystem == nullptr) return;

	QuestActorSubsystem->UnregisterQuestActorComponent(this);
}




void UQuestNotifier::SetIsRelevant(bool bNewIsRelevant, const USuqsTaskState* Task)
{
	bIsRelevant = bNewIsRelevant;

	if (bIsRelevant == true)
	{
		OnTaskAdded(Task);
	}
}









void UQuestNotifier::OnTaskUpdated(const USuqsTaskState* TaskState)
{
	ParentComponent->OnTaskUpdated(TaskState);
}
void UQuestNotifier::OnTaskCompleted(const USuqsTaskState* TaskState)
{
	ParentComponent->OnTaskCompleted(TaskState);
}
void UQuestNotifier::OnTaskFailed(const USuqsTaskState* TaskState)
{
	ParentComponent->OnTaskFailed(TaskState);
}
void UQuestNotifier::OnTaskAdded(const USuqsTaskState* TaskState)
{
	ParentComponent->OnTaskAdded(TaskState);
}
void UQuestNotifier::OnTaskRemoved(const USuqsTaskState* TaskState)
{
	ParentComponent->OnTaskRemoved(TaskState);
}