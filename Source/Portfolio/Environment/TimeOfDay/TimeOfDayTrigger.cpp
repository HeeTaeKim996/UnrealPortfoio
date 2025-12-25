


#include "Environment/TimeOfDay/TimeOfDayTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Environment/TimeOfDay/TimeOfDay.h"
#include "Components/ShapeComponent.h"

ATimeOfDayTrigger::ATimeOfDayTrigger()
{

}


void ATimeOfDayTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TimeOfDay = Cast<ATimeOfDay>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeOfDay::StaticClass()));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATimeOfDayTrigger::OnTriggerBeginOverlap);
}



void ATimeOfDayTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TimeOfDay.IsValid())
	{
		TimeOfDay.Get()->SetDesiredTime(DesiredTime);
	}
}

