

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/R1HighlightInterface.h"
#include "R1Define.h"
#include "System/R1GameplayTags.h"
#include "AbilitySystemInterface.h"
#include "MeleeTrace/Public/MeleeTraceComponent.h"
#include "AbilitySystem/AbilityCommonStruct.h"
#include "Structures/SoundInfo.h"
#include "R1Character.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UR1GameplayAbility;
class UCharacterAbility;
struct FGameplayAbilitySpecHandle;
class UR1AbilitySystemComponent;
struct FOnAttributeChangeData;
class UNiagaraSystem;
struct FTraceHitInfo;


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	FSoundInfo FootstepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FootstepFx;
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
	void SetDesiredVec(FVector InVec);
	FVector GetDesiredVec();
	UNiagaraSystem* GetHitFx() { return BaseSettings.HitFx; }
	void OnFootstepPlan(bool bPlayFx ,const FVector& FootstepPos);

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	FVector DesiredVec = FVector(1, 0, 0);
	bool bUseDesiredVec = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	FBaseSetting BaseSettings;





	/* MeleeTrace */
private:
	UFUNCTION()
	void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle);

	UFUNCTION()
	void HandleTraceHit(const FMeleeHitInfo& HitInfo);

protected:
	virtual bool OnTraceHit(const FMeleeHitInfo& HitInfo);


protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMeleeTraceComponent> MeleeTrace;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_OnTraceHit,
		const FMeleeHitInfo&, MeleeHitInfo, const FTraceHitInfo&, TraceHitInfo);
	FDelegate_OnTraceHit Delegate_OnTraceHit;
	



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



	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TArray<TSubclassOf<UR1GameplayAbility>> StartupAbilities;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCharacterASC> CharacterASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_GAMultiDelegate,
		const FGameplayTag&, InTag);
	FDelegate_GAMultiDelegate Delegate_GAMultiDelegate;
};

