

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayTagContainer.h"
#include "R1AbilityTask.generated.h"

class AR1Character;
class UR1GameplayAbility;
struct FAbilityCancelInfo;
struct FAbilitySuccessInfo;
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


private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnAbilitySuccess(FAbilitySuccessInfo SucessInfo);
	
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnAbilityCancel(FAbilityCancelInfo CancelInfo);

	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnTraceHit(struct FMeleeHitInfo MeleeHitInfo);

protected:
	virtual bool AbilitySuccess(FAbilitySuccessInfo SuccessInfo);
	virtual bool AbilityCancel(FAbilityCancelInfo CancelInfo);
	virtual bool TraceHit(FMeleeHitInfo MeleeHitInfo);

protected:
	UPROPERTY()
	TWeakObjectPtr<AR1Character> WeakCharacter;

	UPROPERTY()
	TWeakObjectPtr<UR1GameplayAbility> WeakAbility;

	FGameplayTag AbilityTag;
};
