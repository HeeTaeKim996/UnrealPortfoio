


#include "AbilitySystem/Abilities/BaseAttackAbility.h"




UBaseAttackAbility::UBaseAttackAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//ensureAlwaysMsgf(StateTag != FGameplayTag::EmptyTag, TEXT("StateTag Is Already Defined"));
	StateTag = R1Tags::State_Action_Attack_Base;
}
