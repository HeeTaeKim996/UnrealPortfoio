


#include "Environment/AmbientCharacter/AmbientCharacter.h"

// Sets default values
AAmbientCharacter::AAmbientCharacter()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAmbientCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmbientCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmbientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

