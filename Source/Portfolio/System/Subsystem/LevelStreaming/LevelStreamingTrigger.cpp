


#include "System/Subsystem/LevelStreaming/LevelStreamingTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "LevelStreamingManager.h"
#include "Components/ShapeComponent.h"


ALevelStreamingTrigger::ALevelStreamingTrigger()
{
	PrimaryActorTick.bCanEverTick = false;


}

void ALevelStreamingTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamingTrigger::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALevelStreamingTrigger::OnTriggerEndOverlap);
}

void ALevelStreamingTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ULevelStreamingManager::Get(this)->AddLevel(LevelAsset, this);
}

void ALevelStreamingTrigger::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ULevelStreamingManager::Get(this)->RemoveLevel(LevelAsset, this);
}

