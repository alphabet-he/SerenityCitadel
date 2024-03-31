// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SerenityCitadel : ModuleRules
{
	public SerenityCitadel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine"
        });
	}
}
