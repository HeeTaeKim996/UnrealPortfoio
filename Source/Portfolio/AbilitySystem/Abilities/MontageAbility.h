

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "MontageAbility.generated.h"

struct FAnimMontageInstance;


UCLASS()
class PORTFOLIO_API UMontageAbilityTask : public UCharacterAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};



UCLASS()
class PORTFOLIO_API UMontageAbility : public UCharacterAbility
{
	GENERATED_BODY()
public:
	UMontageAbility();


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

	virtual void OnMontageBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted);
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterruped);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> PlayingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName InSectionName = NAME_None;

	FAnimMontageInstance* MontageInstance;
};
