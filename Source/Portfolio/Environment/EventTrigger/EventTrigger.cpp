


#include "Environment/EventTrigger/EventTrigger.h"
#include "Components/ShapeComponent.h"

AEventTrigger::AEventTrigger()
	: Super()
{
	
}


void AEventTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEventTrigger::OnTriggerBeginOverlap);
}



void AEventTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	FTriggerInfo TriggerInfo;
	TriggerInfo.TriggeringActor = OtherActor;
	TriggerInfo.TriggerOwner = this;
	Delegate_EventTrigger.Broadcast(TriggerInfo);
}

