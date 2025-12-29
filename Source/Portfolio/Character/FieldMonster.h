

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Monster.h"
#include "FieldMonster.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AFieldMonster : public AR1Monster
{
	GENERATED_BODY()
public:
	AFieldMonster();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void RefreshHpBarRatio(float NewHealth) override;
	
public:
	const bool IsWorking() const { return bIsWorking; }
	const bool IsSleeping() const { return bIsSleeping; }

	void Sleep();
	void Wakeup();
	void DoWork();
	void LeaveWork();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> HpBarComponent; 

	UPROPERTY(EditInstanceOnly, Category = "LevelStreaming")
	TSoftObjectPtr<UWorld> StreamingLevel;

private:
	FName LandLevelName;
	FName LevelStreamingName;

	bool bIsWorking = false;
	bool bIsSleeping = false;
};