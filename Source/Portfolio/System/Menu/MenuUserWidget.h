

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;
class UUserWidget_SaveData;


UCLASS()
class PORTFOLIO_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnLoadButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Continue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Load;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget_SaveData> LoadWidget;
};