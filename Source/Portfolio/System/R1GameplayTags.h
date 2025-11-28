

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

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Label_Preload);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_Test);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_Test2);



	/*-------------------
		    State
	--------------------*/
	/* Life */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Life_Alive);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Life_Dead);

	/* HitState */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitState_Vulnerable);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitState_Invincible);

	/* Action */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Blocking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_UsingItem);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_HitReact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Action_Parry);

	/* Input */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Input_Full);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Input_Disabled);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Input_DodgeOnly);
}
