// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Portfolio : ModuleRules
{
	public Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "Portfolio" });

		PublicDependencyModuleNames.AddRange(new string[] 
		{ "Core", "CoreUObject", "Engine", "InputCore",

			"EnhancedInput"/*EnhancedInput*/, "GameplayTags"/*GameplayTags*/, "NavigationSystem"/*==NavMesh*/,
			"AIModule"/*AIController, BehaviourTree..*/, "Niagara"/*==ParticleEffect*/, "UMG"/* UI */,
			"GameplayTasks" /*GAS*/, "GameplayAbilities"/*GAS*/, 

			/*Plugins*/
			"ModuleTest" /*TEST*/, "MeleeTrace"/* Prevent Hitch Problem In HitDetection*/,


		}); // ※ Moduel Doesnt Change Engine Codes. But Add Module's dll

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
