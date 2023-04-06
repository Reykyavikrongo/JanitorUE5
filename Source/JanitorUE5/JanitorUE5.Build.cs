// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JanitorUE5 : ModuleRules
{
	public JanitorUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
