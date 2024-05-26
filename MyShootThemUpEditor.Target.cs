// My Shoot Them Up Game , All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class MyShootThemUpEditorTarget : TargetRules
{
	public MyShootThemUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "MyShootThemUp" } );
	}
}
