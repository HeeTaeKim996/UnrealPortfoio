

#pragma once

#include "CoreMinimal.h"
#include "MusicData.generated.h"

UENUM(BlueprintType)
enum class EMusicStemRole : uint8
{
	Drums,
	Bass,
	Harmony,
	Melody,
	Perc,
	Sfx
};

USTRUCT(BlueprintType)
struct FMusicStemPool
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMusicStemRole Role = EMusicStemRole::Drums;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<USoundBase>> Variations;
};

UCLASS(BlueprintType)
class UMusicDeckData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int DurationBars = 16;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMusicStemPool> StemPools;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FadeOutSeconds = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FadeInSeconds = 0.05f;
};
