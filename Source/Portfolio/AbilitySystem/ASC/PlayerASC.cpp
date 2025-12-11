


#include "AbilitySystem/ASC/PlayerASC.h"




UPlayerASC::UPlayerASC()
	: Super()
{

}

FGameplayAbilitySpecHandle UPlayerASC::ActivateAbility(FGameplayTag InTag)
{
	if (InTag.MatchesTag(R1Tags::Ability_Action_Attack_BaseAttack))
	{
		ComboCount++;
	}
	else
	{
		ComboCount = 0;
	}

	return Super::ActivateAbility(InTag);
}
