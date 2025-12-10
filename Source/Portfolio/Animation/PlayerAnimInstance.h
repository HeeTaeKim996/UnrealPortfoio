

#pragma once

#include "CoreMinimal.h"
#include "Animation/CharacterAnimInstance.h"
#include "Structures/PlayerUpperBodyState.h"
#include "PlayerAnimInstance.generated.h"

class AR1Character;
class UCharacterMovementComponent;

UENUM(BlueprintType)
enum class EUpperBodyAnimation : uint8
{
	Idle,
	Blocking,
	Aiming
};

UENUM(BlueprintType)
enum class ELowerBodyDir : uint8
{
	Forward,
	Right,
	Left,
	Backward
};

UCLASS()
class PORTFOLIO_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	friend class AR1Player;

public:
	UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> ForwardAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> RightAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> LeftAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> BackwardAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> BlockingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> SprintAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerMotionState PlayerMotionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator UnderRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUpperBodyAnimation UpperBodyAnimation = EUpperBodyAnimation::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELowerBodyDir LowerBodyDir = ELowerBodyDir::Forward;
};
