// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HomeModule : ModuleRules
{
	public HomeModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine",
			"UMG",
            "Slate",
            "SlateCore",
            "InputCore",
            "EnhancedInput",
            "GlobalModule",
            "NinjaCharacter",
            "SerenityCitadel"
        });
	}
}
