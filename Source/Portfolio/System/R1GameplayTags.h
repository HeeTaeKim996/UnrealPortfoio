

#pragma once

#include "NativeGameplayTags.h"


namespace R1Tags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_BaseAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Wheel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Block);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_End);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_IMC_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_UserWidget_MainUserWidget);
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_ETC_GameplayTagContainers);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Label_Preload);




	/*-------------------
			Ability
	--------------------*/
	/* Dead */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Dead);

	/* Action */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action);

	// Attack
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_BaseAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_BaseAttack_TestAttack);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster_FieldMonster_Kronos_Sweep);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster_FieldMonster_Kronos_JumpAttack);

	// HitReact
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact_Knockdown);

	// Parry
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Parry);

	/* Mode */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_Blocking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_UsingItem);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_Aiming);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_Sneaking);
	
	/* HitState */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitState);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitState_Invincible);




	

	/*-------------------
		  GameplayCue
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Test);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_HitReact_HitReaction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Die);
}