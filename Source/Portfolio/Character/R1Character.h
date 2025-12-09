

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
class UR1GameplayAbility;
class UCharacterAbility;
struct FGameplayAbilitySpecHandle;
class UR1AbilitySystemComponent;
struct FOnAttributeChangeData;
class UNiagaraSystem;


USTRUCT(BlueprintType)
struct FBaseSetting
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UR1GameplayAbility> HitReactAbility;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UR1GameplayAbility> KnockdownAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UR1GameplayAbility> DeadAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> HitFx;
};

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



	virtual void OnDead(TObjectPtr<AR1Character> From);



	virtual void HandleGameplayTagEvent(FGameplayTag EventTag);



protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void RefreshHpBarRatio(float NewHealth) {}

	

public:
	void SetDesiredVec(FVector InVec) { DesiredVec = InVec; }
	FVector GetDesiredVec() { return DesiredVec;  }
	UNiagaraSystem* GetHitFx() { return BaseSettings.HitFx; }


protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	FVector DesiredVec = FVector(1, 0, 0);
	bool bUseDesiredVec = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	FBaseSetting BaseSettings;





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
	UR1AbilitySystemComponent* GetR1AbilitySystemComponent();
	virtual void InitAbilitySystem();
	FGameplayAbilitySpecHandle ActivateAbility(FGameplayTag AbilityTag);

	virtual void InitializeCharacterAbilities();
	void AbilityCancel(FGameplayTagContainer CancelTags);

public:
	void AddState(FGameplayTag NewState);
	bool IsInState(FGameplayTag StateTag) const;
	bool IsInAnyState(const FGameplayTagContainer& StateTags);
	bool IsInAllStates(const FGameplayTagContainer& StateTags);


protected:
	UFUNCTION()
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists);




public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGAS_OnAttackSucceed,
		FMeleeHitInfo, MeleeHitInfo);
	FGAS_OnAttackSucceed GAS_OnAttackSucceed;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGAS_OnAttackParried,
		FMeleeHitInfo, MeleeHitInfo);
	FGAS_OnAttackParried GAS_OnAttackParried;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TArray<TSubclassOf<UR1GameplayAbility>> StartupAbilities;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCharacterASC> CharacterASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;
};

