

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "AbilitySystem/Abilities/R1AbilityTask.h"
#include "GameplayTagContainer.h"
#include "Ability_Attack.generated.h"


class AR1Character;


UCLASS()
class PORTFOLIO_API UAbilityTask_Attack : public UR1AbilityTask
{
	GENERATED_BODY()
public:
	void Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter, UAnimMontage* InMontage);

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	virtual bool TraceHit(struct FMeleeHitInfo MeleeHitInfo) override;

	virtual bool AbilitySuccess(FAbilitySuccessInfo InTag) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;
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


