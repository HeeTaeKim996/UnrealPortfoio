

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/R1HighlightInterface.h"
#include "R1Define.h"
#include "System/R1GameplayTags.h"
#include "AbilitySystemInterface.h"
#include "MeleeTrace/Public/MeleeTraceComponent.h"
#include "R1Character.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PORTFOLIO_API AR1Character : public ACharacter, public IR1HighlightInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AR1Character(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;

	virtual void OnDamage(int Damage, TObjectPtr<AR1Character> From);
	virtual void OnDead(TObjectPtr<AR1Character> From);

	

	virtual void HandleGameplayTagEvent(FGameplayTag EventTag);

protected:
	virtual void RefreshHpBarRatio() {}

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();

public:
	ECreatureState GetCreatureState() { return CreatureState; }
	void SetCreatureState(ECreatureState InState) { CreatureState = InState; }
	void SetDesiredVec(FVector InVec) { DesiredVec = InVec; }
	FVector GetDesiredVec() { return DesiredVec;  }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::None;

	FVector DesiredVec = FVector(1, 0, 0);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;

protected:
	UFUNCTION()
	virtual void HandleTraceHit(UMeleeTraceComponent* ThisComponent, AActor* HitActor, const FVector& HitLocation,
		const FVector& HitNormal, FName HitBoneName, FMeleeTraceInstanceHandle TraceHandle, uint8 Protocol);

	UFUNCTION()
	virtual void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	virtual void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle);

public:
	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UR1GameplayAbility>> StartupAbilities;
};
