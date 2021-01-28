// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDown_Assignment : ModuleRules
{
	public TopDown_Assignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
