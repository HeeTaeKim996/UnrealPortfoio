


#include "System/Menu/MenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Continue->OnClicked.AddDynamic(this, &UMenuUserWidget::OnContinueButtonClicked);
}

void UMenuUserWidget::OnContinueButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("MainLevel")));
}