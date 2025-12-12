

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Monster/MonsterAttackAbility.h"
#include "KronosAbility_SweepAttack.generated.h"

UCLASS()
class  PORTFOLIO_API UKronosAbility_SweepAttackTask : public UMonsterAttackAbilityTask
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
class PORTFOLIO_API UKronosAbility_SweepAttack : public UMonsterAttackAbility
{
	GENERATED_BODY()
public:
	UKronosAbility_SweepAttack();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	
};
