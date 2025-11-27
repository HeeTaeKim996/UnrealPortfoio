

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayTagContainer.h"
#include "R1AbilityTask.generated.h"

class AR1Character;
class UR1GameplayAbility;
/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1AbilityTask : public UAbilityTask
{
	GENERATED_BODY()
public:
	void Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter);
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;


protected:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	virtual void OnAbilitySuccess(FGameplayTag InTag);
	
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	virtual void OnAbilityCancel(FGameplayTag InTag);

	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	virtual void OnTraceHit(struct FMeleeHitInfo MeleeHitInfo);


protected:
	UPROPERTY()
	TWeakObjectPtr<AR1Character> WeakCharacter;

	UPROPERTY()
	TWeakObjectPtr<UR1GameplayAbility> WeakAbility;

	FGameplayTag AbilityTag;
};
