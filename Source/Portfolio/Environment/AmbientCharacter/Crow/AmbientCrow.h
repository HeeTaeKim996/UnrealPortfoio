

#pragma once

#include "CoreMinimal.h"
#include "Environment/AmbientCharacter/AmbientCharacter.h"
#include "AmbientCrow.generated.h"

class AEventTrigger;
struct FTriggerInfo;

UCLASS()
class PORTFOLIO_API AAmbientCrow : public AAmbientCharacter
{
	GENERATED_BODY()
public:
	AAmbientCrow();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	UFUNCTION()
	void OnPlayertrigger(const FTriggerInfo& TriggerInfo);

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config")
	TObjectPtr<AEventTrigger> EventTrigger;

public:
	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<UArrowComponent> FlyDirectionArrow;
};
