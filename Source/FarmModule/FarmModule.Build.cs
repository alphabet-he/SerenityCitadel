// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FarmModule : ModuleRules
{
	public FarmModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine",
			"UMG",
			"Slate", 
			"SlateCore",
			"GlobalModule",
			"SerenityCitadel"
        });
	}
}
