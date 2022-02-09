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
			PublicAdditionalLibraries.AddRange(new string[] { System.IO.Path.Combine(ModuleDirectory, "PugiTest", "pugi", "pugixml.lib") });
		}
	}
}
