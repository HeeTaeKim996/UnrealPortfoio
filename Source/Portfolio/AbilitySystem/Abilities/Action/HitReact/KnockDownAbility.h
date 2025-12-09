

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MontageAbility.h"
#include "KnockDownAbility.generated.h"

UCLASS()
class PORTFOLIO_API UKncokDownAbilityTask : public UMontageAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};

UCLASS()
class PORTFOLIO_API UKnockDownAbility : public UMontageAbility
{
	GENERATED_BODY()
public:
	UKnockDownAbility();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


protected:
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterruped) override;
};
