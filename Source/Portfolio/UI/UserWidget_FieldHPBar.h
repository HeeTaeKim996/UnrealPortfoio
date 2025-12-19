

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_FieldHPBar.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UUserWidget_FieldHPBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UUserWidget_FieldHPBar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

public:
	void SetHpRatio(float Ratio);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpBar;
};
