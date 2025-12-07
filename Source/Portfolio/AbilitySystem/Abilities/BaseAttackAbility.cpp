


#include "AbilitySystem/Abilities/BaseAttackAbility.h"




UBaseAttackAbility::UBaseAttackAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_Attack_BaseAttack);
}
