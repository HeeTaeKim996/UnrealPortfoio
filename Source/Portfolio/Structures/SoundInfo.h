

#pragma once

#include "CoreMinimal.h"
#include "SoundInfo.generated.h"

USTRUCT(Blueprintable)
struct PORTFOLIO_API FSoundInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> SoundBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	float Volume = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	float StartTime = 0.f;
};