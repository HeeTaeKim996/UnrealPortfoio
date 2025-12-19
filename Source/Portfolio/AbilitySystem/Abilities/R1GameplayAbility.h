

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/R1Character.h"
#include "GameplayTagContainer.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "R1GameplayAbility.generated.h"

class UR1AbilitySystemComponent;

UCLASS()
class PORTFOLIO_API UR1AbilityTask : public UAbilityTask
{
	GENERATED_BODY()
protected:
	void SuccessAbility();
	void CancelAbility();
};









UCLASS()
class PORTFOLIO_API UR1GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UR1GameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	FORCEINLINE void EndAbilitySuccess()
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
	FORCEINLINE void EndAbilityCancel()
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
};