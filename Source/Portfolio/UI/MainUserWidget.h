

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

class UButton;
class UProgressBar;
class UCanvasPanel;
class UUserWidget_SaveData;



UCLASS()
class PORTFOLIO_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnSaveButtonClicked();

	UFUNCTION()
	void OnLoadButtonClicked();

	UFUNCTION()
	void OnMenuExitButtonClicked();

public:
	void UpdatePlayerHealthBar(float Ratio);
	void UpdatePlayerStaminaBar(float Ratio);
	void UpdateFirstSkillCooldownBar(float Ratio);

	void OpenMenu();
	void CloseMenu();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Root;

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
	TObjectPtr<UButton> Button_Save;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Load;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_MenuExit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget_SaveData> LoadWidget;
};

