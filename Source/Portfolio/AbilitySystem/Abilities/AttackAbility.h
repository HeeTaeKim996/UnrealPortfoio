

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionAbility.h"
#include "AttackAbility.generated.h"

struct FMeleeHitInfo;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct PORTFOLIO_API FAttackInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AttackCoefficient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Impact;
};




UCLASS()
class PORTFOLIO_API UAttackAbilityTask : public UActionAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	UFUNCTION()
	void OnAttackSucceed(const FMeleeHitInfo& MeleeHitInfo);
	
protected:
	virtual bool AttackSucceed(const FMeleeHitInfo& MeleeHitInfo);
};



UCLASS()
class PORTFOLIO_API UAttackAbility : public UActionAbility
{
	GENERATED_BODY()
public:
	UAttackAbility();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FAttackInfo> AttackInfos;

};
