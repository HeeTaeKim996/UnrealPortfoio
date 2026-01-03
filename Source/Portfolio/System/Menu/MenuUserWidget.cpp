


#include "System/Menu/MenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "System/Subsystem/SaveGame/SaveUI/UserWidget_SaveData.h"

void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Continue->OnClicked.AddDynamic(this, &UMenuUserWidget::OnContinueButtonClicked);
	Button_Load->OnClicked.AddDynamic(this, &UMenuUserWidget::OnLoadButtonClicked);

	LoadWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UMenuUserWidget::OnContinueButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("TempLevel")));
}
void UMenuUserWidget::OnLoadButtonClicked()
{
	LoadWidget->SetVisibility(ESlateVisibility::Visible);
}