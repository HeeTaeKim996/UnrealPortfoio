
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AttackAbility.h"
#include "MonsterAttackAbility.generated.h"

UCLASS()
class PORTFOLIO_API UMonsterAttackAbilityTask : public UAttackAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
protected:
	virtual bool AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo) override;

protected:
	TWeakObjectPtr<class AR1Character> WeakTarget;
};






UCLASS()
class PORTFOLIO_API UMonsterAttackAbility : public UAttackAbility
{
	GENERATED_BODY()
public:
	UMonsterAttackAbility();
};
