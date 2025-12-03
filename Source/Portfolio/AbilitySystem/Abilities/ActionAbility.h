

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "ActionAbility.generated.h"


UCLASS()
class PORTFOLIO_API UActionAbilityTask : public UCharacterAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

};



UCLASS()
class PORTFOLIO_API UActionAbility : public UCharacterAbility
{
	GENERATED_BODY()

public:
	UActionAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> PlayingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName SectionName = "";
};
