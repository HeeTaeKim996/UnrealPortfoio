

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

class UButton;
class UProgressBar;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnTestButtonClicked();

	UFUNCTION()
	void OnMenuExitButtonClicked();

public:
	void UpdatePlayerHealthBar(float Ratio);
	void UpdatePlayerStaminaBar(float Ratio);
	void UpdateFirstSkillCooldownBar(float Ratio);

	void OpenMenu();

private:
	void CloseMenu();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TestButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerHpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerStaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> FirstSkiallCooldownBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas_Panel_InGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas_Panel_Menu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_MenuExit;
};

