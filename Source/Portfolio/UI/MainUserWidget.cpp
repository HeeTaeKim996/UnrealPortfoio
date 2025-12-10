


#include "UI/MainUserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

void UMainUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (TestButton)
	{
		TestButton->OnClicked.AddDynamic(this, &UMainUserWidget::OnTestButtonClicked);
	}
}

void UMainUserWidget::OnTestButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan,
		TEXT("MainUserWidget.cpp__DEBUGCHECk"));
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
