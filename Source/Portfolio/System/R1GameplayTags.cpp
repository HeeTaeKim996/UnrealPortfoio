#include "System/R1GameplayTags.h"


namespace R1Tags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_LeftMouse, "Input.Action.LeftMouse");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Wheel, "Input.Action.Wheel");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_RightMouse, "Input.Action.RightMouse");

	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Begin, "Event.Montage.Begin");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_End, "Event.Montage.End");

	UE_DEFINE_GAMEPLAY_TAG(Asset_IMC_Base, "Asset.IMC.Base");
	UE_DEFINE_GAMEPLAY_TAG(Asset_UserWidget_MainUserWidget, "Asset.UserWidget.MainUserWidget");

	UE_DEFINE_GAMEPLAY_TAG(Asset_Label_Preload, "Asset.Label.Preload");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_Test, "Ability.Attack.Test");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_Test2, "Ability.Attack.Test2");



	/*-------------------
			State
	--------------------*/
	/* Life */
	UE_DEFINE_GAMEPLAY_TAG(State_Life_Alive, "State.Life.Alive");
	UE_DEFINE_GAMEPLAY_TAG(State_Life_Dead, "State.Life.Dead");

	/* HitState */
	UE_DEFINE_GAMEPLAY_TAG(State_HitState_Vulnerable, "State.HitState.Vulnerable");
	UE_DEFINE_GAMEPLAY_TAG(State_HitState_Invincible, "State.HitState.Invincible");

	/* Action */
	UE_DEFINE_GAMEPLAY_TAG(State_Action_None, "State.Action.None");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Attack, "State.Action.Attack");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Blocking, "State.Action.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_UsingItem, "State.Action.UsingItem");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_HitReact, "State.Action.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Parry, "State.Action.Parry");

	/* Input */
	UE_DEFINE_GAMEPLAY_TAG(State_Input_Full, "State.Input.Full");
	UE_DEFINE_GAMEPLAY_TAG(State_Input_Disabled, "State.Input.Disabled");
	UE_DEFINE_GAMEPLAY_TAG(State_Input_DodgeOnly, "State.Input.DodgeOnly");
}


