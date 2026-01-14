


#include "Custom/TempQuestTrigger.h"
#include "Components/BoxComponent.h"
#include "Portfolio/System/MainGameStateBase.h"
#include "Public/SuqsGameStateComponent.h"

ATempQuestTrigger::ATempQuestTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(Trigger);

}

void ATempQuestTrigger::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATempQuestTrigger::OnTriggerBeginOverlap);
}




void ATempQuestTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainGameStateBase* MainGameStateBase = GetWorld()->GetGameState<AMainGameStateBase>();
	if (MainGameStateBase == nullptr) return;

	USuqsGameStateComponent* SuqsGameStateComponent = MainGameStateBase->GetSuqsGameStateComponent();
	if (SuqsGameStateComponent == nullptr) return;

	
	SuqsGameStateComponent->StartQuest(QuestID);
}
