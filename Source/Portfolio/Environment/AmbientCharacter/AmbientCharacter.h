

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmbientCharacter.generated.h"

UCLASS()
class PORTFOLIO_API AAmbientCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAmbientCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
