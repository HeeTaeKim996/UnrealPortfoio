

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AttackAbility.h"
#include "AttackAbility_Test.generated.h"

UCLASS()
class PORTFOLIO_API UAttacAbilityTask_Test : public UAttackAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	virtual void OnTraceHit(FMeleeHitInfo MeleeHitInfo) override;

};

UCLASS()
class PORTFOLIO_API UAttackAbility_Test : public UAttackAbility
{
	GENERATED_BODY()
public:
	UAttackAbility_Test(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	
};
