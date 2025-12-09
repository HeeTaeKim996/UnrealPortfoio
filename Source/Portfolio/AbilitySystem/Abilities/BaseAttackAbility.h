

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AttackAbility.h"
#include "BaseAttackAbility.generated.h"

UCLASS()
class PORTFOLIO_API UBaseAttackAbilityTask : public UAttackAbilityTask
{
	GENERATED_BODY()

};


UCLASS()
class PORTFOLIO_API UBaseAttackAbility : public UAttackAbility
{
	GENERATED_BODY()
public:
	UBaseAttackAbility();


};
