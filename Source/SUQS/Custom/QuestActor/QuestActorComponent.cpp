


#include "Custom/QuestActor/QuestActorComponent.h"

UQuestActorComponent::UQuestActorComponent()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestActorComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UQuestActorComponent::IsQuesetComponentActive()
{
	return bEnabled && bIsCurrent;
}



void UQuestActorComponent::SetIsCurrent(bool bNeewIsCurrent)
{
	bIsCurrent = bNeewIsCurrent;


}