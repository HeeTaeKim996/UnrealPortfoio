


#include "Data/DataAsset_GameplayTagContainers.h"
#include "System/R1GameplayTags.h"

UDataAsset_GameplayTagContainers::UDataAsset_GameplayTagContainers()
	: Super()
{
	CantBaseActableTags.AddTagFast(R1Tags::Ability_Dead);
	CantBaseActableTags.AddTagFast(R1Tags::Ability_Action);
	CantBaseActableTags.AddTagFast(R1Tags::Ability_Mode_UsingItem);


	OnActionCall_CancelingTags.AddTagFast(R1Tags::Ability_Mode_Blocking);
	OnActionCall_CancelingTags.AddTagFast(R1Tags::Ability_Mode_Sneaking);


	OnHitReact_CancelTags.AddTagFast(R1Tags::Ability_Action);
	OnHitReact_CancelTags.AddTagFast(R1Tags::Ability_Mode);
}
