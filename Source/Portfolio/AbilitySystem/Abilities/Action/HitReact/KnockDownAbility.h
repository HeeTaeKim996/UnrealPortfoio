

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionAbility.h"
#include "KnockDownAbility.generated.h"

class UAnimMontage;
struct FGameplayTag;

UCLASS()
class PORTFOLIO_API UKncokDownAbilityTask : public UActionAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void OnDelegate_GAMultiDelegate(const FGameplayTag& InTag);
};

UCLASS()
class PORTFOLIO_API UKnockDownAbility : public UActionAbility
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
public:
	void OnGetup();

private:
	bool bIsInvincible;
};
