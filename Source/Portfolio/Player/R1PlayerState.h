

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "R1PlayerState.generated.h"

class UR1AbilitySystemComponent;
class UPlayerASC;
class UR1AttributeSet;
struct FGameplayTagContainer;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AR1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UR1AbilitySystemComponent* GetR1AbilitySystemComponent() const;
	UR1AttributeSet* GetR1PlayerSet() const;


public:
	bool GetCooldownRemainingForTags(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPlayerASC> ASC;

	UPROPERTY()
	TObjectPtr<UR1AttributeSet> PlayerSet;
};
