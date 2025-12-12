

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MontageAbility.h"
#include "ActionAbility.generated.h"


UCLASS()
class PORTFOLIO_API UActionAbilityTask : public UMontageAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

};








UCLASS()
class PORTFOLIO_API UActionAbility : public UMontageAbility
{
	GENERATED_BODY()

public:
	UActionAbility();


protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	virtual void OnMontageBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted) override;
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterruped) override;


};
