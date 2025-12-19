


#include "Environment/AmbientCharacter/Crow/AmbientCrow.h"
#include "Environment/EventTrigger/EventTrigger.h"
#include "Environment/AmbientCharacter/Crow/AI_AmbientCrow.h"
#include "Components/ArrowComponent.h"

AAmbientCrow::AAmbientCrow()
	: Super()
{
	FlyDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FlyDirectionArrow"));
	FlyDirectionArrow->SetupAttachment(GetRootComponent());
}

void AAmbientCrow::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(EventTrigger, TEXT("Event Trigger is Not assigned"));
	EventTrigger->Delegate_EventTrigger.AddDynamic(this, &AAmbientCrow::OnPlayertrigger);
}

void AAmbientCrow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EventTrigger)
	{
		EventTrigger->Delegate_EventTrigger.RemoveDynamic(this, &AAmbientCrow::OnPlayertrigger);
	}
}

void AAmbientCrow::OnPlayertrigger(const FTriggerInfo& TriggerInfo)
{
	AAI_AmbientCrow* CrowCon = Cast<AAI_AmbientCrow>(GetController());
	ensureAlwaysMsgf(CrowCon, TEXT("Controller is not CrowController"));

	CrowCon->StartFly();


	TriggerInfo.TriggerOwner->Destroy();
}
