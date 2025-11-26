

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1Define.h"
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
	void TickCursorTrace();
	void ChaseTargetAndAttack();

private:
	void Input_Move(const FInputActionValue& InputValue);

	void OnWheelStarted();
	void OnWheelTriggered();
	void OnWheelReleased();

	void OnLeftMouseStarted();
	void OnLeftMouseTriggered();
	void OnLeftMouseReleased();

	void OnRightMouseStarted();
	void OnRightMouseTriggered();
	void OnRightMouseReleased();

	ECreatureState GetCreatureState();
	void SetCreatureState(ECreatureState InState);

public:
	FVector GetCursorPos() { return CursorPos; }
	UMainUserWidget* GetMainUI() { return MainUI; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	FVector CursorPos;
	float cursorPushedTime;
	bool bWheelPressed = false;

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
	/* // Obsolate_BlueprintAssign
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> TestAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> TurnAction;
	*/
};
