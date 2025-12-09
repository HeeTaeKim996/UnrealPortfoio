


#include "AbilitySystem/Abilities/BaseAttackAbility.h"




UBaseAttackAbility::UBaseAttackAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_Attack_BaseAttack);
}
