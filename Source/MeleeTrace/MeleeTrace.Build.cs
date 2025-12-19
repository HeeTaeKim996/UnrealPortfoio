// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ※ Reference : https://github.com/rlewicki/MeleeTrace/tree/master

public class MeleeTrace : ModuleRules
{
    public MeleeTrace(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DeveloperSettings"/* Enable ProjectSetting Modify */,
                "GameplayTags", 
            }
        );
    }
}
