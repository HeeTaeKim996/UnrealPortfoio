

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CostAttackAbility.h"
#include "BaseAttackAbility.generated.h"

UCLASS()
class PORTFOLIO_API UBaseAttackAbilityTask : public UCostAttackAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	virtual bool AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo) override;
private:
	void OnPlayerBaseAttackOn(FGameplayTag InAbilityTag);
};


UCLASS()
class PORTFOLIO_API UBaseAttackAbility : public UCostAttackAbility
{
	GENERATED_BODY()
public:
	UBaseAttackAbility();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxComboCount = 4;

	int ComboIndex;
};