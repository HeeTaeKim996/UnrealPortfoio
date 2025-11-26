

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

class UButton;

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

public:
	void UpdatePlayerHealthBar(float Ratio);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TestButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PlayerHpBar;
};
