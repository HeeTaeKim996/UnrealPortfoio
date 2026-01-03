


#include "UI/MainUserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "System/Subsystem/SaveGame/SaveDataManager.h"
#include "Components/CanvasPanel.h"
#include "Player/R1PlayerController.h"
#include "System/Subsystem/SaveGame/SaveUI/UserWidget_SaveData.h"

void UMainUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Save)
	{
		Button_Save->OnClicked.AddDynamic(this, &UMainUserWidget::OnSaveButtonClicked);
	}
	if (Button_Load)
	{
		Button_Load->OnClicked.AddDynamic(this, &UMainUserWidget::OnLoadButtonClicked);
	}
	if (Button_MenuExit)
	{
		Button_MenuExit->OnClicked.AddDynamic(this, &UMainUserWidget::OnMenuExitButtonClicked);
	}

	LoadWidget->SetVisibility(ESlateVisibility::Collapsed);
	CloseMenu();
}

void UMainUserWidget::OnSaveButtonClicked()
{
	USaveDataManager* SaveDataManager = USaveDataManager::Get(this);
	if (SaveDataManager)
	{
		SaveDataManager->SaveCurrent();
	}
}

void UMainUserWidget::OnLoadButtonClicked()
{
	LoadWidget->SetVisibility(ESlateVisibility::Visible);
}

void UMainUserWidget::OnMenuExitButtonClicked()
{
	AR1PlayerController* PC = Cast<AR1PlayerController>(GetWorld()->GetFirstPlayerController());
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetMenuOpenFalse();

	CloseMenu();
}

void UMainUserWidget::UpdatePlayerHealthBar(float Ratio)
{
	PlayerHpBar->SetPercent(Ratio);
}

void UMainUserWidget::UpdatePlayerStaminaBar(float Ratio)
{
	PlayerStaminaBar->SetPercent(Ratio);
}

void UMainUserWidget::UpdateFirstSkillCooldownBar(float Ratio)
{
	FirstSkiallCooldownBar->SetPercent(Ratio);
}

void UMainUserWidget::CloseMenu()
{
	Canvas_Panel_InGame->SetVisibility(ESlateVisibility::Visible);
	Canvas_Panel_Menu->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainUserWidget::OpenMenu()
{
	Canvas_Panel_InGame->SetVisibility(ESlateVisibility::Hidden);
	Canvas_Panel_Menu->SetVisibility(ESlateVisibility::Visible);
}
