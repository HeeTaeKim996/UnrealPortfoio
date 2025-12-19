


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
	UpperBodyAnimation = EUpperBodyAnimation::Idle;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AR1Player* R1Player = Cast<AR1Player>(OwnerCharacter);
	if (!R1Player) return;

	PlayerMotionState = R1Player->GetPlayerMotionState();
	if (PlayerMotionState == EPlayerMotionState::Split || PlayerMotionState == EPlayerMotionState::Split_Angle)
	{
		if (PlayerMotionState == EPlayerMotionState::Split_Angle)
		{
			FVector DesiredVec = R1Player->GetDesiredVec();
			DesiredVec.Normalize();
			FVector MoveVec = R1Player->GetCharacterMovement()->GetCurrentAcceleration();
			MoveVec.Z = 0;
			MoveVec.Normalize();

			float Dot = DesiredVec.Dot(MoveVec);
			float CrossZ = DesiredVec.Cross(MoveVec).Z;
			float Angle = FMath::RadiansToDegrees(FMath::Atan2(CrossZ, Dot)); // ※ Possible Because two vectors are span of x,y

			//DebugMessage(FString::Printf(TEXT("PlayerAnimInstance : [%f], [%f]"), Dot, Angle));

			float Alpha = FMath::Clamp(DeltaSeconds * 180.f, 0.f, 360.f);
			//float Alpha = 8.f;

			if (Dot > COS_45)
			{
				LowerBodyDir = ELowerBodyDir::Forward;
				UnderRotation.Yaw = FMath::FixedTurn(UnderRotation.Yaw, Angle, Alpha);

				//DebugMessage(TEXT("PlayerAnimInstance : Forward"));
			}
			else if (Dot > -COS_45)
			{
				if (CrossZ > 0.f)
				{
					LowerBodyDir = ELowerBodyDir::Left;
					//UnderRotation.Yaw = Angle - 90;

					UnderRotation.Yaw = FMath::FixedTurn(UnderRotation.Yaw, Angle - 90, Alpha);

					//DebugMessage(TEXT("PlayerAnimInstance : Left"));
				}
				else
				{
					LowerBodyDir = ELowerBodyDir::Right;
					//UnderRotation.Yaw = Angle + 90;
					UnderRotation.Yaw = FMath::FixedTurn(UnderRotation.Yaw, Angle + 90, Alpha);

					//DebugMessage(TEXT("PlayerAnimInstance : Right"));
				}
			}
			else
			{
				LowerBodyDir = ELowerBodyDir::Backward;

				//UnderRotation.Yaw = 180 + Angle;
				UnderRotation.Yaw = FMath::FixedTurn(UnderRotation.Yaw, 180 + Angle, Alpha);

				//DebugMessage(TEXT("PlayerAnimInstance : Backward"));
			}
		}
		

		if (R1Player->IsInState(R1Tags::Ability_Mode_Blocking))
		{
			UpperBodyAnimation = EUpperBodyAnimation::Blocking;
			//DebugMessage(TEXT("PlayerAnimInstance : Blocking"));
		}
		else
		{
			UpperBodyAnimation = EUpperBodyAnimation::Idle;
			//DebugMessage(TEXT("PlayerAnimInstance : Idle"));
		}
	}

	bIsSprint =	R1Player->IsSprint();
	
}


