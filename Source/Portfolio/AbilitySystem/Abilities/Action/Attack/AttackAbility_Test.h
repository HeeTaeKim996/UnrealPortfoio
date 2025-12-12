

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseAttackAbility.h"
#include "AttackAbility_Test.generated.h"

UCLASS()
class PORTFOLIO_API UAttacAbilityTask_Test : public UBaseAttackAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	virtual bool AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo) override;

};

UCLASS()
class PORTFOLIO_API UAttackAbility_Test : public UBaseAttackAbility
{
	GENERATED_BODY()
public:
	UAttackAbility_Test();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
