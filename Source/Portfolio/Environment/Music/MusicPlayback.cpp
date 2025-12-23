


#include "Environment/Music/MusicPlayback.h"

AMusicPlayback::AMusicPlayback()
	: Super()
{

}

void AMusicPlayback::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusicPlayback::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusicPlayback::StartPlayMusic()
{
}

void AMusicPlayback::EndPlayMusic()
{
}

void AMusicPlayback::AnnouncePrepareNext()
{
	FMusicPlaybackAnnounce PlaybackAnnounce;
	PlaybackAnnounce.Owner = this;
	PlaybackAnnounce.AnnounceType = EAnnounceType::PrepareNext;

	Delegate_Announce.ExecuteIfBound(PlaybackAnnounce);
}

