

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "R1AnimInstance.generated.h"

class AR1Player;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UR1AnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AR1Player> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
};
