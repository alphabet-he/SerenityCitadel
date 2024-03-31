// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GlobalModule : ModuleRules
{
	public GlobalModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine",
			"UMG",
			"SerenityCitadel",
			"InputCore",
			"EnhancedInput"
		});
	}
}
