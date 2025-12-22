

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_Music.generated.h"

class FObjectPreSaveContext;

USTRUCT(BlueprintType)
struct FMusicBarEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Bar = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MusicProtocol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> Sound;
};

UCLASS(BlueprintType)
class PORTFOLIO_API UDataAsset_Music : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalBars = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMusicBarEvent> Events;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGameplayTag> Stems;

#if WITH_EDITOR
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;


private:
	void SortEvents();
#endif
};
