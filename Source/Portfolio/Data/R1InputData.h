

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "R1InputData.generated.h"

class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FR1InputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;
};

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1InputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FR1InputAction> InputActions;
};
