


#include "Environment/EventTrigger/EventTrigger_Box.h"
#include "Components/BoxComponent.h"


class UBoxComponent;
AEventTrigger_Box::AEventTrigger_Box()
	: Super()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(Trigger);
}
