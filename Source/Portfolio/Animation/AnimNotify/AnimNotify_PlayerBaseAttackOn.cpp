


#include "Animation/AnimNotify/AnimNotify_PlayerBaseAttackOn.h"
#include "Animation/PlayerAnimInstance.h"
#include "Character/R1Player.h"

UAnimNotify_PlayerBaseAttackOn::UAnimNotify_PlayerBaseAttackOn()
	: Super()
{
}

void UAnimNotify_PlayerBaseAttackOn::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	UCharacterAnimInstance* CharacterAnimInst = Cast<UCharacterAnimInstance>(MeshComp->GetAnimInstance());
	if (!CharacterAnimInst) return;

	AR1Player* R1Player = Cast<AR1Player>(CharacterAnimInst->GetOwnerCharacter());
	if (!R1Player) return;

	R1Player->OnPlayerBaseAttackOn(AbilityTag);
}
