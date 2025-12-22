


#include "Environment/EventTrigger/Execute/EventExecuteTrigger_Box.h"
#include "Components/BoxComponent.h"

AEventExecuteTrigger_Box::AEventExecuteTrigger_Box()
	: Super()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(Trigger);
}
