

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
	virtual void RefreshHpBarRatio(float NewHealth) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> HpBarComponent; // @@ Will Be Replaced By AssetManager
	
};