

#pragma once

#include "CoreMinimal.h"
#include "Animation/CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class AR1Character;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
