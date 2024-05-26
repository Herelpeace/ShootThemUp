// My Shoot Them Up Game , All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class MyShootThemUpTarget : TargetRules
{
	public MyShootThemUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "MyShootThemUp" } );
	}
}
