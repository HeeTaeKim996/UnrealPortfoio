using UnrealBuildTool;
using System.IO;

public class SUQS : ModuleRules
{
	public SUQS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				"SUQS"
            }
            );

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"UMG",

                "Portfolio" // Temp for Test
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
