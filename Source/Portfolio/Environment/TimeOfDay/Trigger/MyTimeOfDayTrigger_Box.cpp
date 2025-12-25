


#include "Environment/TimeOfDay/Trigger/MyTimeOfDayTrigger_Box.h"
#include "Components/BoxComponent.h"

AMyTimeOfDayTrigger_Box::AMyTimeOfDayTrigger_Box()
	: Super()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	Trigger->SetCollisionProfileName("PlayerDetector");
}
