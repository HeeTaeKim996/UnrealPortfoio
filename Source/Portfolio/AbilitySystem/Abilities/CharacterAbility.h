

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "AbilitySystem/AbilityCommonStruct.h"
#include "CharacterAbility.generated.h"

class AR1Character;
class UCharacterASC;
class UCharacterAbility;

UCLASS()
class PORTFOLIO_API UCharacterAbilityTask : public UR1AbilityTask
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	
protected:
	FGameplayTag AbilityTag;
};



UCLASS()
class PORTFOLIO_API UCharacterAbility : public UR1GameplayAbility
{
	GENERATED_BODY()
public:
	UCharacterAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
