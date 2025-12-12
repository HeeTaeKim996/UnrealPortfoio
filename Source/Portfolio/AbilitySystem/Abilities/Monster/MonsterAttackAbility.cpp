


#include "AbilitySystem/Abilities/Monster/MonsterAttackAbility.h"
#include "Character/R1Monster.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Structures/TraceHitInfo.h"

void UMonsterAttackAbilityTask::Activate()
{
	Super::Activate();

	AR1Monster* R1Monster = Cast<AR1Monster>(GetAvatarActor());
	if (R1Monster == nullptr) return;

	AAIController* AIcon = Cast<AAIController>(R1Monster->GetController());
	if (AIcon == nullptr) return;

	UBlackboardComponent* BB = AIcon->GetBlackboardComponent();
	if (BB == nullptr) return;

	UObject* TargetObj = BB->GetValueAsObject("TargetCharacter");
	if (TargetObj == nullptr) return;

	AR1Character* TargetCharacter = Cast<AR1Character>(TargetObj);
	if (TargetCharacter == nullptr) return;

	WeakTarget = TargetCharacter;
}

void UMonsterAttackAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

bool UMonsterAttackAbilityTask::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Super::AttackSucceed(MeleeHitInfo, TraceHitInfo) == false) return false;

	return true;
}











UMonsterAttackAbility::UMonsterAttackAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_Attack_Monster);

}