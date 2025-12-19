


#include "Environment/AmbientCharacter/Crow/Anim_Crow.h"
#include "Environment/AmbientCharacter/Crow/AmbientCrow.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnim_Crow::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Crow::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AAmbientCrow* Crow = Cast<AAmbientCrow>(GetOwningActor());
	if (Crow)
	{
		MoveSpeed = Crow->GetCharacterMovement()->Velocity.Size2D();
	}
}
