// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class gameAPK : ModuleRules
{
	public gameAPK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ImageWrapper" });

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string TestPugiPath = System.IO.Path.Combine(ModuleDirectory, "TestPugi");

			PublicAdditionalLibraries.AddRange(new string[] { System.IO.Path.Combine(TestPugiPath, "pugiXML", "pugixml.lib", "a") });

		
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch", "ApplicationCore" });
            PrivateIncludePaths.AddRange(new string[] { "/Source/Runtime/Launch/Private" });
            string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("PhotoLibrary", System.IO.Path.Combine(pluginPath, "PhotoLibrary_APL.xml","a"));
        }
		
    }

    


}
