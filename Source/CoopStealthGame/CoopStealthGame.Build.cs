// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoopStealthGame : ModuleRules
{
	public CoopStealthGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
