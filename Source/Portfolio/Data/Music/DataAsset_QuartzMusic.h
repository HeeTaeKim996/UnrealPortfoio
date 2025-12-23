

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_QuartzMusic.generated.h"

class FObjectPreSaveContext;

UENUM(BlueprintType)
enum class EQuartzUnitType
{
	Bar,
	Beat
};

USTRUCT(BlueprintType)
struct FMusicBarEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Unit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Stem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> Sound;
};


UCLASS()
class PORTFOLIO_API UDataAsset_QuartzMusic : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMusicBarEvent> Events;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> Stems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuartzUnitType UnitType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BPM;

#if WITH_EDITOR
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;


private:
	void SortEvents();
#endif
};
