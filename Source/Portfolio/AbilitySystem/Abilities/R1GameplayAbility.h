

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "R1GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	

public:
	FORCEINLINE virtual void EndAbilitySuccessfuly() 
	{ 
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false); 
	}

		
};
