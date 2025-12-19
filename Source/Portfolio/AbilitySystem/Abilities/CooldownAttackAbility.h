

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CostAttackAbility.h"
#include "CooldownAttackAbility.generated.h"

UCLASS()
class PORTFOLIO_API UCooldownAttackAbilityTask : public UCostAttackAbilityTask
{
	GENERATED_BODY()
};


UCLASS()
class PORTFOLIO_API UCooldownAttackAbility : public UCostAttackAbility
{
	GENERATED_BODY()
	
protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const override;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	FScalableFloat CooldownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	FGameplayTagContainer CooldownTags;

	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;
};