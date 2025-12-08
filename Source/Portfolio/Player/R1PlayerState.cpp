


#include "Player/R1PlayerState.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"

AR1PlayerState::AR1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UPlayerASC>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(false); // Singple Play
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full); // SinglePlay

	PlayerSet = CreateDefaultSubobject<UR1AttributeSet>("PlayerSet");
}

UAbilitySystemComponent* AR1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1AbilitySystemComponent* AR1PlayerState::GetR1AbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1AttributeSet* AR1PlayerState::GetR1PlayerSet() const
{
	return PlayerSet;
}
