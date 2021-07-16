// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class B1 : ModuleRules
{
	public B1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"GameplayTasks",
			"NavigationSystem",
			"Niagara"
		});

		PublicIncludePaths.AddRange(new string[] { 
			"B1/Public/Player",
			"B1/Public/Dev",
			"B1/Public/HUD",
			"B1/Public/Weapon",
			"B1/Public/Components",
			"B1/Public/Animations",
			"B1/Public/Pickups",
			"B1/Public/AI"
		});
	}
}
