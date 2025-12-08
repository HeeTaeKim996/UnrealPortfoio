

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "DeathAbility.generated.h"

UCLASS()
class PORTFOLIO_API UDeathAbilityTask : public UCharacterAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};


UCLASS()
class PORTFOLIO_API UDeathAbility : public UCharacterAbility
{
	GENERATED_BODY()
public:
	UDeathAbility();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


protected:
	void PlayMontage(class UR1AbilitySystemComponent* R1ASC, UAnimMontage* Montage, FName SectionName);

	void OnMontageEnded(UAnimMontage* Montage, bool bInterruped);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> PlayingMontage;

	UPROPERTY()
	FName InSectionName = NAME_None;
};
