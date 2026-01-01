


#include "UI/MainUserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "System/Subsystem/SaveGame/SaveDataManager.h"
#include "Components/CanvasPanel.h"
#include "Player/R1PlayerController.h"

void UMainUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (TestButton)
	{
		TestButton->OnClicked.AddDynamic(this, &UMainUserWidget::OnTestButtonClicked);
	}
	if (Button_MenuExit)
	{
		Button_MenuExit->OnClicked.AddDynamic(this, &UMainUserWidget::OnMenuExitButtonClicked);
	}

	CloseMenu();
}

void UMainUserWidget::OnTestButtonClicked()
{
	USaveDataManager* SaveDataManager = USaveDataManager::Get(this);

	SaveDataManager->TempLoad();
	SaveDataManager->TempSave();
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
