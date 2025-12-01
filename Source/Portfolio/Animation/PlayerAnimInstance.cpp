


#include "Animation/PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/R1Player.h"
#include "R1Define.h"

UPlayerAnimInstance::UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	UpperBodyState = EUpperBodyState::Idle;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AR1Player* R1Player = Cast<AR1Player>(OwnerCharacter);
	if (!R1Player) return;

	bIsUpperLowerSplit = R1Player->IsUpperLowerSplit();
	if (bIsUpperLowerSplit)
	{
		FVector DesiredVec = R1Player->GetDesiredVec();
		FVector MoveVec = R1Player->GetCharacterMovement()->GetCurrentAcceleration();
		MoveVec.Z = 0;
		MoveVec.Normalize();

		float Dot = DesiredVec.Dot(MoveVec);
		float CrossZ = DesiredVec.Cross(MoveVec).Z;
		float Angle = FMath::RadiansToDegrees(FMath::Atan2(CrossZ, Dot));

		if (Dot > COS45)
		{
			LowerBodyDir = ELowerBodyDir::Forward;
			UnderRotation.Yaw = Angle;
		}
		else if (Dot > -COS45)
		{
			if (CrossZ > 0.f)
			{
				LowerBodyDir = ELowerBodyDir::Left;
				UnderRotation.Yaw = Angle - 90;
			}
			else
			{
				LowerBodyDir = ELowerBodyDir::Right;
				UnderRotation.Yaw = Angle + 90;
			}
		}
		else
		{
			LowerBodyDir = ELowerBodyDir::Backward;
			
			UnderRotation.Yaw = 180 + Angle;
		}

		if (R1Player->IsInState(R1Tags::State_Mode_Blocking))
		{
			UpperBodyState = EUpperBodyState::Blocking;
		}
	}
}


