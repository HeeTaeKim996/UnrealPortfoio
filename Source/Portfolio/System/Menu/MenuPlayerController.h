

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

class UMenuUserWidget;

UCLASS()
class PORTFOLIO_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMenuPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<UMenuUserWidget> MenuUI;
};
