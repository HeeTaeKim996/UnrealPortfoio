

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

class UButton;
class UProgressBar;

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
	void UpdatePlayerStaminaBar(float Ratio);
	void UpdateFirstSkillCooldownBar(float Ratio);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TestButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerHpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerStaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> FirstSkiallCooldownBar;
};

