// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class gameAPK : ModuleRules
{
	public gameAPK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string TestPugiPath = System.IO.Path.Combine(ModuleDirectory, "TestPugi");

			PublicAdditionalLibraries.AddRange(new string[] { System.IO.Path.Combine(TestPugiPath, "pugiXML", "pugixml.lib", "a") });
		}
	}
}
