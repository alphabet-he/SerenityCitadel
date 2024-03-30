// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SerenityCitadelEditorTarget : TargetRules
{
	public SerenityCitadelEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("SerenityCitadel");
		ExtraModuleNames.Add("FarmModule");
		ExtraModuleNames.Add("GeneralCodes");
		ExtraModuleNames.Add("HomeModule");
    }
}
