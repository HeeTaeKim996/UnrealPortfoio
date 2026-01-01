

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1Define.h"
#include "GameplayTagContainer.h"
#include "R1PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class UNiagaraSystem;
class AR1Player;
class AR1Character;
class IR1HighlightInterface;
class AR1Monster;
class UMainUserWidget;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AR1PlayerController(const FObjectInitializer& objectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;


private:
	void UpdatePlyaerRotation();
	void TickCursorTrace();
	void ChaseTargetAndAttack();

public:
	void SetMenuOpenFalse() { bMenuOpen = false; } // Temp

private:
	void Input_Move(const FInputActionValue& InputValue);
	void OnMoveReleased(const FInputActionValue& InputValue);

	void OnWheelStarted();
	void OnWheelTriggered();
	void OnWheelReleased();

	void OnBaseAttackKeyStarted();
	void OnBaseAttackKeyTriggered();
	void OnBaseAttackKeyReleased();

	void OnBlockKeyStarted();
	void OnBlockKeyTriggered();
	void OnBlockKeyReleased();

	void OnDodgeKeyStarted();
	void OnDodgeKeyTriggered();
	void OnDodgeKeyReleased();

	void OnToggleMenuStarted();

public:
	void OnFirstSkillTagChanged(const FGameplayTag CallbackTag, int NewCount);

public:
	FVector GetCursorPos() { return CursorPos; }
	UMainUserWidget* GetMainUI() { return MainUI; }

	UFUNCTION(Exec)
	void TimeOfDay_SetTime(float SetTime);

	UFUNCTION(Exec)
	void TimeOfDay_SetDesiredTime(float DesiredTime);


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	bool bMenuOpen = false;
	FVector CursorPos;
	float cursorPushedTime;
	bool bWheelPressed = false;
	bool bMovePressed = false;
	float DodgePushedTime;

protected:
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<AR1Monster> TargetMonster;

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IR1HighlightInterface> Highlighted;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AR1Player> R1Player;


protected:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//TSubclassOf<class UUserWidget> HudWidget;
	// TSubclassOf : Holds Class Type.		TObjectPtr : Holds Class Instance

	UPROPERTY()
	TObjectPtr<UMainUserWidget> MainUI;

protected:
	bool bIsFirstSkillable = true;

	TMap<FGameplayTag, FGameplayTag> InputToAbilityMap;
};
