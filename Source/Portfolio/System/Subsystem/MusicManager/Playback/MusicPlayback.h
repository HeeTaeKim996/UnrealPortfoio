

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicPlayback.generated.h"

class AMusicPlayback;

UENUM()
enum class EAnnounceType
{
	MusicFinished,
	
};

USTRUCT()
struct FMusicPlaybackAnnounce
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<AMusicPlayback> Owner;

	UPROPERTY()
	EAnnounceType AnnounceType;
};



UCLASS()
class PORTFOLIO_API AMusicPlayback : public AActor
{
	GENERATED_BODY()

public:
	AMusicPlayback();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartPlayMusic();
	virtual void EndPlayMusic();


protected:
	void AnnounceMusicFinished();

public:
	DECLARE_DELEGATE_OneParam(FDelegate_Announce,
		const FMusicPlaybackAnnounce& MusicPlaybackAnnounce);
	FDelegate_Announce Delegate_Announce;

};
