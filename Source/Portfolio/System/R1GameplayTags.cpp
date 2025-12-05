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
	//UE_DEFINE_GAMEPLAY_TAG(Asset_ETC_GameplayTagContainers, "Asset.ETC.GameplayTagContainers");

	UE_DEFINE_GAMEPLAY_TAG(Asset_Label_Preload, "Asset.Label.Preload");





	/*-------------------
		  Ability
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_Test, "Ability.Attack.Test");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_Test2, "Ability.Attack.Test2");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base, "Ability.Action.HitReact.Base");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base_Fwd, "Ability.Action.HitReact.Base.Fwd");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base_Right, "Ability.Action.HitReact.Base.Right");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base_Left, "Ability.Action.HitReact.Base.Left");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base_Bwd, "Ability.Action.HitReact.Base.Bwd");




	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Blocking, "Ability.Mode.Blocking");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Monster_FieldMonster_Kronos_Sweep, "Ability.Monster.FieldMonster.Kronos.Sweep");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Monster_FieldMonster_Kronos_JumpAttack, "Ability.Monster.FieldMonster.Kronos.JumpAttack");

	/*-------------------
			State
	--------------------*/
	/// Dead
	UE_DEFINE_GAMEPLAY_TAG(State_Dead, "State.Dead");

	/// HitState
	UE_DEFINE_GAMEPLAY_TAG(State_HitState, "State.HitState");
	UE_DEFINE_GAMEPLAY_TAG(State_HitState_Invincible, "State.HitState.Invincible");

	/* Attack */
	UE_DEFINE_GAMEPLAY_TAG(State_Action, "State.Action");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Attack, "State.Action.Attack");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Attack_Base, "State.Action.Attack.Base");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Attack_Skill, "State.Action.Attack.Skill");

	UE_DEFINE_GAMEPLAY_TAG(State_Action_UsingItem, "State.Action.UsingItem");

	// HitReact
	UE_DEFINE_GAMEPLAY_TAG(State_Action_HitReact, "State.Action.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_HitReact_Base, "State.Action.HitReact.Base");
	UE_DEFINE_GAMEPLAY_TAG(State_Action_HitReact_Knockdown, "State.Action.HitReact.Knockdown");


	UE_DEFINE_GAMEPLAY_TAG(State_Action_Parry, "State.Action.Parry");

	/// Mode
	UE_DEFINE_GAMEPLAY_TAG(State_Mode, "State.Mode");
	UE_DEFINE_GAMEPLAY_TAG(State_Mode_Blocking, "State.Mode.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(State_Mode_UsingItem, "State.Mode.UsingItem");
	UE_DEFINE_GAMEPLAY_TAG(State_Mode_Aiming, "State.Mode.Aiming");
	UE_DEFINE_GAMEPLAY_TAG(State_Mode_Sneaking, "State.Mode.Sneaking");

	/* Die */
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Die, TEXT("State.Action.Die"));
	UE_DEFINE_GAMEPLAY_TAG(State_Action_Die_Normal, TEXT("State.Action.Die.Normal"));


	/*-------------------
	      GameplayCue
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Test, "GameplayCue.Test");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_HitReact_HitReaction, "GameplayCue.HitReact.HitReaction");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Die, TEXT("GameplayCue.Die"));
}


