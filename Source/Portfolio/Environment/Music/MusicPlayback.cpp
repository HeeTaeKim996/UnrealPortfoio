


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
	AnnounceMusicFinished();
}

void AMusicPlayback::AnnounceMusicFinished()
{
	FMusicPlaybackAnnounce PlaybackAnnounce;
	PlaybackAnnounce.Owner = this;
	PlaybackAnnounce.AnnounceType = EAnnounceType::MusicFinished;

	Delegate_Announce.ExecuteIfBound(PlaybackAnnounce);
}

