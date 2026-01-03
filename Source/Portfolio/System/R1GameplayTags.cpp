#include "System/R1GameplayTags.h"


namespace R1Tags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_BaseAttack, "Input.Action.BaseAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill_1, "Input.Action.Skill.1");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Wheel, "Input.Action.Wheel");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Block, "Input.Action.Block");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Dodge, "Input.Action.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Input_ETC_ToggleMenu, "Input.ETC.ToggleMenu");

	/*-------------------
			Event
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Begin, "Event.Montage.Begin");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_End, "Event.Montage.End");

	UE_DEFINE_GAMEPLAY_TAG(Event_Player_BaseAttackOn, "Event.Player.BaseAttackOn");

	UE_DEFINE_GAMEPLAY_TAG(Event_GAS, "Event.GAS");
	UE_DEFINE_GAMEPLAY_TAG(Event_GAS_DeadStop, "Event.GAS.DeadStop");
	UE_DEFINE_GAMEPLAY_TAG(Event_GAS_KnockdownGetup, "Event.GAS.KnockdownGetup");
	UE_DEFINE_GAMEPLAY_TAG(Event_GAS_AttackSoundStart, "Event.GAS.AttackSoundStart");

	/*-------------------
			Asset
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_IMC_Base, "Asset.IMC.Base");
	UE_DEFINE_GAMEPLAY_TAG(Asset_UserWidget_UserWidgets, "Asset.UserWidget.UserWidgets");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_Label_Preload, "Asset.Label.Preload");

	UE_DEFINE_GAMEPLAY_TAG(Asset_GE, "Asset.GE");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_InitializePlayerSet, "Asset.GE.InitializePlayerSet");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_InitializeMonsterSet, "Asset.GE.InitializeMonsterSet");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_Initializer, "Asset.GE.Initializer");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_Initializer_GEs, "Asset.GE.Initializer.GEs");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_Initializer_PlayerStamina, "Asset.GE.Initializer.PlayerStamina");
	UE_DEFINE_GAMEPLAY_TAG(Asset_GE_Initializer_NoPlayerStaminable, "Asset.GE.Initializer.NoPlayerStaminable");

	// Event
	UE_DEFINE_GAMEPLAY_TAG(Asset_Music_Event_PrepareNext, "Asset.Music.Event.PrepareNext");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Music_Event_ChangeMusic, "Asset.Music.Event.ChangeMusic");

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

	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Skill, "Ability.Action.Attack.Skill");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Skill_CooldownAttack, "Ability.Action.Attack.Skill.CooldownAttack");


	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster, "Ability.Action.Attack.Monster");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster_FieldMonster_Kronos_Sweep, "Ability.Action.Attack.Monster.FieldMonster.Kronos.Sweep");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Attack_Monster_FieldMonster_Kronos_JumpAttack, "Ability.Action.Attack.Monster.FieldMonster.Kronos.JumpAttack");



	// HitReact
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact, "Ability.Action.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Base, "Ability.Action.HitReact.Base");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_HitReact_Knockdown, "Ability.Action.HitReact.Knockdown");


	// Parry
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Parry, "Ability.Action.Parry");

	/* Mode */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode, "Ability.Mode");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Blocking, "Ability.Mode.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_UsingItem, "Ability.Mode.UsingItem");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Aiming, "Ability.Mode.Aiming");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Sneaking, "Ability.Mode.Sneaking");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Mode_Sprint, "Ability.Mode.Sprint");

	/* HitState */
	UE_DEFINE_GAMEPLAY_TAG(Ability_HitState, "Ability.HitState");
	UE_DEFINE_GAMEPLAY_TAG(Ability_HitState_Invincible, "Ability.HitState.Invincible");

	/* Cooldown */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Cooldown_AssignLocation_First, "Ability.Cooldown.AssignLocation.First");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Cooldown_AssignLocation_Second, "Ability.Cooldown.AssignLocation.Second");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Cooldown_AssignLocation_Third, "Ability.Cooldown.AssignLocation.Third");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Cooldown_CooldownAttack, "Ability.Cooldown.CooldownAttack");

	/* MotionState */
	UE_DEFINE_GAMEPLAY_TAG(Ability_MotionState_None, "Ability.MotionState.None");
	UE_DEFINE_GAMEPLAY_TAG(Ability_MotionState_UpperSplit, "Ability.MotionState.UpperSplit");
	UE_DEFINE_GAMEPLAY_TAG(Ability_MotionState_UpperAngleSplit, "Ability.MotionState.UpperAngleSplit");

	/* ETC */
	UE_DEFINE_GAMEPLAY_TAG(Ability_ETC_NoStaminaRegen, "Ability.ETC.NoStaminaRegen");

	/*-------------------
	      GameplayCue
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_HitReact_HitReaction, "GameplayCue.HitReact.HitReaction");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_HitReact_HitImpact, "GameplayCue.HitReact.HitImpact");


	/*-------------------
		    Data
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Data_GESpec_AttackCoefficient, "Data.GESpec.AttackCoefficient");
	UE_DEFINE_GAMEPLAY_TAG(Data_GESpec_Impact, "Data.GESpec.Impact");
	UE_DEFINE_GAMEPLAY_TAG(Data_SetByCaller_Cooldown, "Data.SetByCaller.Cooldown");
	UE_DEFINE_GAMEPLAY_TAG(Data_SetByCaller_StaminaRegen, "Data.SetByCaller.StaminaRegen");
	UE_DEFINE_GAMEPLAY_TAG(Data_SetByCaller_MitigatedStaminaRegen, "Data.SetByCaller.MitigatedStaminaRegen");
}


