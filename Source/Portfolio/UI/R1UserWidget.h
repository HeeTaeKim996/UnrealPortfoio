

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "R1UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UR1UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;


};