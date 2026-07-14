using UnrealBuildTool;
using System.Collections.Generic;

public class NaughtyBotTarget : TargetRules
{
	public NaughtyBotTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("NaughtyBot");
	}
}
