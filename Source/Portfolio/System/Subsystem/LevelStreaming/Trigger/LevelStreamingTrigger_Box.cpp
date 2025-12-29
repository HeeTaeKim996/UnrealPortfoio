


#include "System/Subsystem/LevelStreaming/Trigger/LevelStreamingTrigger_Box.h"
#include "Components/BoxComponent.h"

ALevelStreamingTrigger_Box::ALevelStreamingTrigger_Box()
	: Super()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	Trigger->SetCollisionProfileName("PlayerDetector");
}
