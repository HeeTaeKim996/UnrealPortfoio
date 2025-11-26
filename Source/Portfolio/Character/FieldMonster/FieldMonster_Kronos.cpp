


#include "Character/FieldMonster/FieldMonster_Kronos.h"
#include "Character/R1Player.h"

AFieldMonster_Kronos::AFieldMonster_Kronos()
	: Super()
{
	
}

void AFieldMonster_Kronos::BeginPlay()
{
	Super::BeginPlay();
}

void AFieldMonster_Kronos::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AFieldMonster_Kronos::HandleTraceHit(UMeleeTraceComponent* ThisComponent, AActor* HitActor, 
	const FVector& HitLocation, const FVector& HitNormal, FName HitBoneName, 
	FMeleeTraceInstanceHandle TraceHandle, uint8 Protocol)
{
	Super::HandleTraceHit(ThisComponent, HitActor, HitLocation, HitNormal, HitBoneName, TraceHandle,
		Protocol);
}

void AFieldMonster_Kronos::HandleTraceStarted(UMeleeTraceComponent* ThisComponent, 
	FMeleeTraceInstanceHandle TraceHandle)
{
	Super::HandleTraceStarted(ThisComponent, TraceHandle);
}

void AFieldMonster_Kronos::HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount, 
	FMeleeTraceInstanceHandle TraceHandle)
{
	Super::HandleTraceEnded(ThisComponent, HitCount, TraceHandle);
}
