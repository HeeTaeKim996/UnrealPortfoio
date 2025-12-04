


#include "Data/DataAsset_GameplayTagContainers.h"
#include "System/R1GameplayTags.h"

UDataAsset_GameplayTagContainers::UDataAsset_GameplayTagContainers()
	: Super()
{
	OnHitReact_CancelTags.AddTagFast(R1Tags::State_Action);
	OnHitReact_CancelTags.AddTagFast(R1Tags::State_Mode);
}
