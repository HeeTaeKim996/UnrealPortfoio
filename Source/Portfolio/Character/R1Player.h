

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "System/R1GameplayTags.h"
#include "Structures/PlayerUpperBodyState.h"
#include "R1Player.generated.h"

class UPlayerAnimInstance;
class UAnimMontage;
class UGameplayEffect;

USTRUCT()
struct PORTFOLIO_API FDeflectInfo
{
	GENERATED_BODY()

	double Start;
	double End = -1;
	double ParrySuccedableTime;
};

UENUM()
enum class EGAState : uint8
{
	None,
	BaseAttackCancellable,
	ActionContinuable
};

UCLASS()
class PORTFOLIO_API AR1Player : public AR1Character
{
	GENERATED_BODY()
	
public:
	AR1Player();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilitySystem() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReasion) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleGameplayTagEvent(FGameplayTag EventTag) override;
	void OnPlayerBaseAttackOn(FGameplayTag EventTag);

private:
	UFUNCTION() // ※ Require UFUNCTION To Use ( Using Delegate Func )
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual bool OnTraceHit(const FMeleeHitInfo& HitInfo) override;


protected:
	virtual void RefreshHpBarRatio(float NewHealth) override;
	void RefreshStaminaBarRatio(const FOnAttributeChangeData& Data);

protected:
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

public:
	void Input_ActivateAbility(FGameplayTag AbilityTag);
	void Input_Block();
	
	void Input_Cancel(FGameplayTagContainer InCancelStates);
	
private:
	bool IsAbilityActivatable(const FGameplayTag& InActionTag);

public:
	EPlayerMotionState GetPlayerMotionState() { return MotionState; }
	const TArray<FDeflectInfo>& GetDeflectInfos() { return DeflectInfos; }
	bool IsSprint() { return bIsSprint; }

private:
	void FinishMotionAlert();
	void StartMotionAlert();

private:
	void OnBlockTagChanged(const FGameplayTag CallbackTag, int NewCount);
	void OnSprintTagChanged(const FGameplayTag CallbackTag, int NewCount);
	void OnUpperSplitTagChanged(const FGameplayTag CallbackTag, int NewCount);
	void OnUpperAngleSplitTagChanged(const FGameplayTag CallbackTag, int NewCount);
	void OnMotionNoneTagChanged(const FGameplayTag CallbackTag, int NewCount);

public:
	EGAState GetGAState() { return GAState; }
	void SetGAState(EGAState SetState) { GAState = SetState; }

protected:
	TArray<FDeflectInfo> DeflectInfos;
	int DeflectMax = 10;
	EGAState GAState = EGAState::None;

private:
	EPlayerMotionState MotionState = EPlayerMotionState::None;
	bool bIsMotionStateAlert = false;
	float MotionAlertTime;

	bool bIsSprint = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	TObjectPtr<UPlayerAnimInstance> PlayerAnim;

	UPROPERTY()
	TObjectPtr<UMeshComponent> PlayerMesh;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharMovement;

public:
	DECLARE_DELEGATE_OneParam(FDelegate_OnBaseAttackOn,
		FGameplayTag AbilityTag);
	FDelegate_OnBaseAttackOn Delegate_OnBaseAttackOn;
};
