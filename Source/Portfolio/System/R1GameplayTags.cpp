#include "System/R1GameplayTags.h"


namespace R1Tags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_BaseAttack, "Input.Action.BaseAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Wheel, "Input.Action.Wheel");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Block, "Input.Action.Block");

	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Begin, "Event.Montage.Begin");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_End, "Event.Montage.End");

	UE_DEFINE_GAMEPLAY_TAG(Asset_IMC_Base, "Asset.IMC.Base");
	UE_DEFINE_GAMEPLAY_TAG(Asset_UserWidget_MainUserWidget, "Asset.UserWidget.MainUserWidget");
	//UE_DEFINE_GAMEPLAY_TAG(Asset_ETC_GameplayTagContainers, "Asset.ETC.GameplayTagContainers");

	UE_DEFINE_GAMEPLAY_TAG(Asset_Label_Preload, "Asset.Label.Preload");




	/*-------------------
			Ability
	--------------------*/

	/* Dead */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Dead, "Ability.Dead");

	/* Action */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action, "Ability.Action");

	// Attack
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack, "Ability.Action.Attack");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_BaseAttack, "Ability.Action.Attack.BaseAttack");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_BaseAttack_TestAttack, "Ability.Action.Attack.BaseAttack.TestAttack");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster, "Ability.Action.Attack.Monster");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster_FieldMonster_Kronos_Sweep, "Ability.Action.Attack.Monster.FieldMonster.Kronos.Sweep");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster_FieldMonster_Kronos_JumpAttack, "Ability.Action.Attack.Monster.FieldMonster.Kronos.JumpAttack");

	// HitReact
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact, "Ability.Action.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base, "Ability.Action.HitReact.Base");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Knockdown, "Ability.Action.HitReact.Knockdown");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Getup, "Ability.Action.HitReact.Getup");


	// Parry
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Parry, "Ability.Action.Parry");

	/* Mode */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode, "Ability.Mode");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Blocking, "Ability.Mode.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_UsingItem, "Ability.Mode.UsingItem");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Aiming, "Ability.Mode.Aiming");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Sneaking, "Ability.Mode.Sneaking");

	/* HitState */
	UE_DEFINE_GAMEPLAY_TAG(Ability_HitState, "Ability.HitState");
	UE_DEFINE_GAMEPLAY_TAG(Ability_HitState_Invincible, "Ability.HitState.Invincible");




	/*-------------------
	      GameplayCue
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Test, "GameplayCue.Test");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_HitReact_HitReaction, "GameplayCue.HitReact.HitReaction");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Die, TEXT("GameplayCue.Die"));
}


