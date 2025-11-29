

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

	

private:
	UFUNCTION(meta = (AllowPrviateAccess = "true"))
	void OnAbilityCancel(FAbilityCancelInfo CancelInfo);

protected:
	bool AbilityCancel(FAbilityCancelInfo CancelInfo);

protected:
	FGameplayTag AbilityTag;
};



UCLASS()
class PORTFOLIO_API UCharacterAbility : public UR1GameplayAbility
{
	GENERATED_BODY()
	

};
