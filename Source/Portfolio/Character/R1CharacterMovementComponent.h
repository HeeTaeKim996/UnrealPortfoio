

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "R1CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UR1CharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
