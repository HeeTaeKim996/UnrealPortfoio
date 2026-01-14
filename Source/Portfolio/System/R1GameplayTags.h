

#pragma once

#include "NativeGameplayTags.h"


namespace R1Tags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_BaseAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Wheel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Block);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Dodge);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_ETC_ToggleMenu);

	/*-------------------
			Event
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_End);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_BaseAttackOn);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_GAS);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_GAS_DeadStop);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_GAS_KnockdownGetup);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_GAS_AttackSoundStart);


	/*-------------------
		    Asset
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_IMC_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_UserWidget_UserWidgets);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Label_Preload);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_InitializePlayerSet);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_InitializeMonsterSet);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_Initializer);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_Initializer_GEs);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_Initializer_PlayerStamina);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_Initializer_NoPlayerStaminable);


	// Event
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Music_Event_PrepareNext);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Music_Event_ChangeMusic);

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

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Skill);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Skill_CooldownAttack);

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
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Mode_Sprint);
	
	/* HitState */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitState);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitState_Invincible);
	
	/* Cooldown */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_First);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_Second);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_Third);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_CooldownAttack);

	/* MotionState */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_MotionState_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_MotionState_UpperSplit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_MotionState_UpperAngleSplit);

	/* ETC */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ETC_NoStaminaRegen);


	/*-------------------
		  GameplayCue
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_HitReact_HitReaction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_HitReact_HitImpact);

	/*-------------------
	        Data
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_GESpec_AttackCoefficient);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_GESpec_Impact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_SetByCaller_Cooldown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_SetByCaller_StaminaRegen);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_SetByCaller_MitigatedStaminaRegen);



	/*-------------------
			Quest
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_FirstQuest);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_FirstQuest_FirstObject_FirstTask);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_FirstQuest_FirstObject_SecondTask);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_FirstQuest_SecondObject_FirstTask);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_SecondQuest);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Main_SecondQuest_FirstObject_FirstTask);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Sub);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Branch);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_Label);

}