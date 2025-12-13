


#include "Data/DataAsset_GameplayTagContainers.h"
#include "System/R1GameplayTags.h"

UDataAsset_GameplayTagContainers::UDataAsset_GameplayTagContainers()
	: Super()
{
	BaseAbilityBlockTgs.AddTagFast(R1Tags::Ability_Dead);
	BaseAbilityBlockTgs.AddTagFast(R1Tags::Ability_Action);
	BaseAbilityBlockTgs.AddTagFast(R1Tags::Ability_Mode_UsingItem);
	BaseAbilityBlockTgs.AddTagFast(R1Tags::Ability_Mode_Aiming);


	OnActionCall_BaseCancelingTags.AddTagFast(R1Tags::Ability_Action);
	OnActionCall_BaseCancelingTags.AddTagFast(R1Tags::Ability_Mode_Blocking);
	OnActionCall_BaseCancelingTags.AddTagFast(R1Tags::Ability_Mode_Sneaking);
	OnActionCall_BaseCancelingTags.AddTagFast(R1Tags::Ability_Mode_Sprint);


	OnHitReact_CancelTags.AddTagFast(R1Tags::Ability_Action);
	OnHitReact_CancelTags.AddTagFast(R1Tags::Ability_Mode);

#if 0 // Obsolate
	PlayerNotRegenableTags.AddTagFast(R1Tags::Ability_Action);
	PlayerNotRegenableTags.AddTagFast(R1Tags::Ability_ETC_NoStaminaRegen);
#endif
}
