

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"

class USuqsGameStateComponent;
class USuqsProgression;
class UDataTable;

UCLASS()
class PORTFOLIO_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMainGameStateBase();

public:
	void Initialize_SuqsGameStateComponent();
	void TempSaveSuqsData();

public:
	USuqsGameStateComponent* GetSuqsGameStateComponent();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USuqsGameStateComponent> SuqsGameStateComponent;


protected:
	// Temps
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UDataTable*> TempTables; 

	UPROPERTY()
	TObjectPtr<USuqsProgression> MainProgression; // Temp
};
