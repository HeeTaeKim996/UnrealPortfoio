


#include "Environment/EventTrigger/Execute/EventExecuteTrigger.h"
#include "Components/ShapeComponent.h"

AEventExecuteTrigger::AEventExecuteTrigger()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEventExecuteTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEventExecuteTrigger::OnTriggerBeginOverlap);
}

void AEventExecuteTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTriggerInfo TriggerInfo;
	TriggerInfo.TriggeringActor = OtherActor;
	TriggerInfo.TriggerOwner = this;
	Delegate_EventExecuteTrigger.ExecuteIfBound(TriggerInfo);
}
