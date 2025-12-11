


#include "AbilitySystem/ASC/PlayerASC.h"




UPlayerASC::UPlayerASC()
	: Super()
{

}

void UPlayerASC::BeginPlay()
{
	Super::BeginPlay();

	LastComboTime = GetWorld()->TimeSeconds;
}

FGameplayAbilitySpecHandle UPlayerASC::ActivateAbility(FGameplayTag InTag)
{
	if (InTag.MatchesTag(R1Tags::Ability_Action_Attack_BaseAttack))
	{
		double CurrentTime = GetWorld()->TimeSeconds;
		if (CurrentTime - LastComboTime < 0.3)
		{
			ComboCount++;
		}
		else
		{
			ComboCount = 1;
		}
	}
	else
	{
		ComboCount = 0;
	}

	return Super::ActivateAbility(InTag);
}
