

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AttackAbility.h"
#include "CostAttackAbility.generated.h"

UCLASS()
class PORTFOLIO_API UCostAttackAbilityTask : public UAttackAbilityTask
{
	GENERATED_BODY()


};


UCLASS()
class PORTFOLIO_API UCostAttackAbility : public UAttackAbility
{
	GENERATED_BODY()
public:
	UCostAttackAbility();

public:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cost")
	FScalableFloat StaminaCost;
};
