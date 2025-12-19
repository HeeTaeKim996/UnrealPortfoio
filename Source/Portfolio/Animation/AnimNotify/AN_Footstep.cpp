


#include "Animation/AnimNotify/AN_Footstep.h"
#include "Animation/CharacterAnimInstance.h"
#include "Character/R1Character.h"

UAN_Footstep::UAN_Footstep()
	: Super()
{
}

void UAN_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	UCharacterAnimInstance* CharacterAnimInst = Cast<UCharacterAnimInstance>(MeshComp->GetAnimInstance());
	if (!CharacterAnimInst) return;

	AR1Character* R1Character = CharacterAnimInst->GetOwnerCharacter();
	if (!R1Character) return;

	FVector FootstepPos;
	bool bPlayFx = true;

	if (bIsRightPlam)
	{
		if (MeshComp->DoesSocketExist("ball_rSocket") == false)
		{
			bPlayFx = false;
		}
			

		FootstepPos = MeshComp->GetSocketLocation("ball_rSocket");
	}
	else
	{
		if (MeshComp->DoesSocketExist("ball_lSocket") == false)
		{
			bPlayFx = false;
		}

		FootstepPos = MeshComp->GetSocketLocation("ball_lSocket");
	}

	R1Character->OnFootstepPlan(bPlayFx, FootstepPos);
}
