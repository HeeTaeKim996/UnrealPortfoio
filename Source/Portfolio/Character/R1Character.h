

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;

	virtual void OnDamage(int Damage, TObjectPtr<AR1Character> From);
	virtual void OnDead(TObjectPtr<AR1Character> From);

	virtual void ToLoco();

	virtual void HandleGameplayTagEvent(FGameplayTag EventTag);



protected:
	virtual void RefreshHpBarRatio() {}

	

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
	bool bUseDesiredVec = true;







	/* MeleeTrace */
protected:
	UFUNCTION()
	virtual void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	virtual void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	virtual void HandleTraceHit(FMeleeHitInfo HitInfo);



protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMeleeTraceComponent> MeleeTrace;








	/* GAS */
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();
	void ActivateAbility(FGameplayTag AbilityTag);

	virtual void AddCharacterAbilities();
	virtual void EndAbilitySuccess(FGameplayTag InTag);


public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitySuccess,
		FGameplayTag, InTag);
	FOnAbilitySuccess OnAbilitySuccess;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraceHit,
		FMeleeHitInfo, MeleeHitInfo);
	FOnTraceHit OnTraceHit;

protected:
	
	virtual void CancelAbilities();

	
protected:
	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UR1GameplayAbility>> StartupAbilities;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;
};

