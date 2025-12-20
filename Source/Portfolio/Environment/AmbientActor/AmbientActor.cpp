


#include "Environment/AmbientActor/AmbientActor.h"

// Sets default values
AAmbientActor::AAmbientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmbientActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmbientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

