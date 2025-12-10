

#pragma once

#include "NativeGameplayTags.h"


namespace R1Tags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_BaseAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Wheel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Block);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_End);


	/*-------------------
		    Asset
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_IMC_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_UserWidget_MainUserWidget);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Label_Preload);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_InitializePlayerSet);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_GE_InitializeMonsterSet);



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
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_CooldownAttack);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster_FieldMonster_Kronos_Sweep);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Attack_Monster_FieldMonster_Kronos_JumpAttack);

	// HitReact
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact_Base);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact_Knockdown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_HitReact_Getup);

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
	
	/* Cooldown */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_First);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_Second);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_AssignLocation_Third);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Cooldown_CooldownAttack);

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
}