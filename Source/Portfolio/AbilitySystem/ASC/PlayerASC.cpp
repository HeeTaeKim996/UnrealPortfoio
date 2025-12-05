


#include "AbilitySystem/ASC/PlayerASC.h"




UPlayerASC::UPlayerASC()
	: Super()
{
	InputToAbilityMap.Add(R1Tags::State_Action_Attack_Base, R1Tags::Ability_Attack_Test);
	InputToAbilityMap.Add(R1Tags::State_Mode_Blocking, R1Tags::Ability_Mode_Blocking);
}

void UPlayerASC::Action(FGameplayTag InStateTag)
{
	ensureAlwaysMsgf(InputToAbilityMap.Contains(InStateTag), TEXT("Not Assgiend StateTag"));
	ActivateAbility(InputToAbilityMap[InStateTag]);
}

