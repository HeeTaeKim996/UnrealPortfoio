

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/R1HighlightInterface.h"
#include "R1Define.h"
#include "System/R1GameplayTags.h"
#include "AbilitySystemInterface.h"
#include "MeleeTrace/Public/MeleeTraceComponent.h"
#include "AbilitySystem/AbilityCommonStruct.h"
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
	void SetDesiredVec(FVector InVec) { DesiredVec = InVec; }
	FVector GetDesiredVec() { return DesiredVec;  }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;


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
	void AbilityCancel(FAbilityCancelInfo CancelInfo);

public:
	void AddState(FGameplayTag NewState);
	bool IsInState(FGameplayTag StateTag) const;
	bool IsInAnyState(const FGameplayTagContainer& StateTags);
	bool IsInAllStates(const FGameplayTagContainer& StateTags);


protected:
	UFUNCTION()
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists);


public:


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGAS_OnTraceHit,
		FMeleeHitInfo, MeleeHitInfo);
	FGAS_OnTraceHit GAS_OnTraceHit;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGAS_OnAbilityCancel,
		FAbilityCancelInfo, CancelInfo);
	FGAS_OnAbilityCancel GAS_OnAbilityCancel;



	
protected:
	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UR1GameplayAbility>> StartupAbilities;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCharacterASC> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;
};

