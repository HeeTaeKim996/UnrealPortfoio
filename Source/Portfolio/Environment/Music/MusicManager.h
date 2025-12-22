

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"


class UQuartzClockHandle;

UCLASS()
class PORTFOLIO_API AMusicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AMusicManager();

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintCallable)
	void Test1();

	UFUNCTION(BlueprintCallable)
	void Test2();

	UFUNCTION(BlueprintCallable)
	void Test3();

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<USoundBase> T1Sound;


	UPROPERTY(EditAnywhere, Category = "Config")
	TObjectPtr<USoundBase> T2Sound;

private:
	UPROPERTY()
	UQuartzClockHandle* ClockHandle;

	UPROPERTY()
	TObjectPtr<UAudioComponent> Sound1;

	UPROPERTY()
	TObjectPtr<UAudioComponent> Sound2;

};
