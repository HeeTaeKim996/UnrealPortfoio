


#include "AbilitySystem/ASC/PlayerASC.h"


UPlayerASC::UPlayerASC(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputToAbilityMap.Add(R1Tags::State_Action_Attack_Base, R1Tags::Ability_Attack_Test);
}

void UPlayerASC::Action(FGameplayTag InStateTag)
{
	ensureAlwaysMsgf(InputToAbilityMap.Contains(InStateTag), TEXT("Not Assgiend StateTag"));
	ActivateAbility(InputToAbilityMap[InStateTag]);
}

