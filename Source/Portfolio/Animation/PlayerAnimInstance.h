

#pragma once

#include "CoreMinimal.h"
#include "Animation/CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class AR1Character;
class UCharacterMovementComponent;

UENUM(BlueprintType)
enum class EUpperBodyState : uint8
{
	Idle,
	Shielding,
	Aiming
};

UCLASS()
class PORTFOLIO_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUpperLowerSplit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator UnderRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUpperBodyState UpperBodyState = EUpperBodyState::Idle;
};
