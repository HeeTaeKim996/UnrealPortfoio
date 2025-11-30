


#include "Player/R1PlayerState.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "AbilitySystem/Attributes/R1PlayerSet.h"

AR1PlayerState::AR1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UPlayerASC>("AbilitySystemComponent");
	PlayerSet = CreateDefaultSubobject<UR1PlayerSet>("PlayerSet");
}

UAbilitySystemComponent* AR1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1AbilitySystemComponent* AR1PlayerState::GetR1AbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1PlayerSet* AR1PlayerState::GetR1PlayerSet() const
{
	return PlayerSet;
}
