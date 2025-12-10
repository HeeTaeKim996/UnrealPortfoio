


#include "AbilitySystem/ASC/PlayerASC.h"




UPlayerASC::UPlayerASC()
	: Super()
{
	InputToAbilityMap.Add(R1Tags::Input_Action_BaseAttack, 
		R1Tags::Ability_Action_Attack_BaseAttack_TestAttack);
	InputToAbilityMap.Add(R1Tags::Input_Action_Block, R1Tags::Ability_Mode_Blocking);
	InputToAbilityMap.Add(R1Tags::Input_Action_Skill_1, R1Tags::Ability_Action_Attack_CooldownAttack);
}

FGameplayAbilitySpecHandle UPlayerASC::ActivateAbilityByInputMap(FGameplayTag InStateTag)
{
	ensureAlwaysMsgf(InputToAbilityMap.Contains(InStateTag), TEXT("Not Assgiend StateTag"));
	return ActivateAbility(InputToAbilityMap[InStateTag]);
}


