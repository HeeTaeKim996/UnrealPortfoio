
#include "Custom/TempTestActor.h"
#include "Custom/QuestActor/QuestActorComponent.h"
#include "Components/BoxComponent.h"
#include "Portfolio/System/MainGameStateBase.h"
#include "Public/SuqsGameStateComponent.h"
#include "Suqs.h"

ATempTestActor::ATempTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(Trigger);


	QuestActorComponent = CreateDefaultSubobject<UQuestActorComponent>(TEXT("QuestActorComponent"));
}

void ATempTestActor::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATempTestActor::OnTriggerBeginOverlap);
}


void ATempTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATempTestActor::QuestActor_OnRegister(const FQuestActor_RegisterInfo& RegisterInfo)
{
	for (const USuqsTaskState* TaskStates : RegisterInfo.RelevantTasks)
	{
		if (TaskStates->GetQuestIdentifier() == QuestID &&
			TaskStates->GetIdentifier() == TaskID)
		{
			return;
		}
	}
	
	QuestActorComponent->SleepOwner();
}

void ATempTestActor::QuestActor_Update(const FQuestActor_UpdateInfo& UpdateInfo)
{
}

void ATempTestActor::QuestActor_Complete(const FQuestActor_CompleteInfo& CompleteInfo)
{
}

void ATempTestActor::QuestActor_Fail(const FQuestActor_FailInfo& FailInfo)
{
}

void ATempTestActor::QuestActor_TaskAdded(const FQuestActor_TaskAddedInfo& TaskAddedInfo)
{
	const USuqsTaskState* TaskState = TaskAddedInfo.AddedTask;

	if (TaskState->GetQuestIdentifier() == QuestID &&
		TaskState->GetIdentifier() == TaskID)
	{
		QuestActorComponent->WakeupOwner();
	}
}

void ATempTestActor::QuestActor_TaskRemoved(const FQuestActor_TaskRemovedInfo& TaskRemovedInfo)
{
}






void ATempTestActor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainGameStateBase* MainGameStateBase = GetWorld()->GetGameState<AMainGameStateBase>();
	if (MainGameStateBase)
	{
		//FString Msg = FString::Printf(TEXT("TempTestActor.cpp : OnBeginOverlap :  [%s], [%s]"),
		//	*QuestID.ToString(), *TaskID.ToString());
		//LogMsg(*Msg);


		MainGameStateBase->GetSuqsGameStateComponent()->ProgressTask(QuestID, TaskID);
	}
}