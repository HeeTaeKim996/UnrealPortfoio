

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "R1PlayerState.generated.h"

class UR1AbilitySystemComponent;
class UR1PlayerSet;

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
	UR1PlayerSet* GetR1PlayerSet() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UR1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UR1PlayerSet> PlayerSet;
};
