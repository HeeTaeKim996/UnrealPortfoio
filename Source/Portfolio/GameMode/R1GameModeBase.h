

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "R1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	bool bUsePlayerStartPos = false;
};
