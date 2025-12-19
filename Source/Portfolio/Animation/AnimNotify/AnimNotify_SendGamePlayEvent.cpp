


#include "Animation/AnimNotify/AnimNotify_SendGamePlayEvent.h"
#include "Animation/CharacterAnimInstance.h"
#include "Character/R1Character.h"

UAnimNotify_SendGamePlayEvent::UAnimNotify_SendGamePlayEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UAnimNotify_SendGamePlayEvent::Notify(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	UCharacterAnimInstance* CharacterAnimInst = Cast<UCharacterAnimInstance>(MeshComp->GetAnimInstance());
	if (!CharacterAnimInst) return;

	AR1Character* R1Character = CharacterAnimInst->GetOwnerCharacter();
	if (!R1Character) return;

	R1Character->HandleGameplayTagEvent(GameplayEventTag);
}
