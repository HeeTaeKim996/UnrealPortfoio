


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

const USuqsTaskState* UQuestNotifier::Initialize_Notifier(UQuestActorComponent* InParent)
{
	ParentComponent = InParent;


	return Register();
}

void UQuestNotifier::OnRemove_Notifier()
{
	UnRegister();
}

const USuqsTaskState* UQuestNotifier::Register()
{
	if (bIsRegistered == true) return nullptr;

	const UGameInstance* GI = GetWorld()->GetGameInstance();
	if (GI == nullptr) return nullptr;

	UQuestActorSubsystem* QuestActorSubsystem = GI->GetSubsystem<UQuestActorSubsystem>();
	if (QuestActorSubsystem == nullptr) return nullptr;

	const USuqsTaskState* Task = QuestActorSubsystem->RegisterQuestActorComponent(this, bIsRelevant);
	if (bIsRelevant)
	{
		return Task;
	}
	

	return nullptr;
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