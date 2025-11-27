

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayTagContainer.h"
#include "Ability_Attack.generated.h"


class AR1Character;


UCLASS()
class PORTFOLIO_API UAbilityTask_Attack : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_Attack* CreateTask(UR1GameplayAbility* OwningAbility, AR1Character* R1Player, 
		UAnimMontage* AttackMontage);

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	UFUNCTION()
	void OnTraceHit(struct FMeleeHitInfo MeleeHitInfo);

	UFUNCTION()
	void OnAbilitySuccess(FGameplayTag InTag);
	
	UPROPERTY()
	TWeakObjectPtr<AR1Character> WeakCharacter;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY()
	TWeakObjectPtr<UR1GameplayAbility> WeakAbility;
};



UCLASS()
class PORTFOLIO_API UAbility_Attack : public UR1GameplayAbility
{
	GENERATED_BODY()
public:
	UAbility_Attack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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
	TObjectPtr<UAnimMontage> AttackMontage;
};


