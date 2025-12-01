

#pragma once

#include "NativeGameplayTags.h"


namespace R1Tags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_LeftMouse);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Wheel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_RightMouse);




	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_End);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_IMC_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_UserWidget_MainUserWidget);
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_ETC_GameplayTagContainers);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Label_Preload);




	/*-------------------
			Ability
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_Test);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_Test2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_Blocking);


	/*-------------------
		    State
	--------------------*/
	/* Dead */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dead);

	/* HitState */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitState);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitState_Invincible);

	/* Action */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Attack_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Attack_Skill);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_UsingItem);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_HitReact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Knockdown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Parry);

	/* Mode */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Mode);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Mode_Blocking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Mode_UsingItem);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Mode_Aiming);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Mode_Sneaking);
}