// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PCombat : ModuleRules
{
	public PCombat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PCombat",
			"PCombat/Variant_Platforming",
			"PCombat/Variant_Platforming/Animation",
			"PCombat/Variant_Combat",
			"PCombat/Variant_Combat/AI",
			"PCombat/Variant_Combat/Animation",
			"PCombat/Variant_Combat/Gameplay",
			"PCombat/Variant_Combat/Interfaces",
			"PCombat/Variant_Combat/UI",
			"PCombat/Variant_SideScrolling",
			"PCombat/Variant_SideScrolling/AI",
			"PCombat/Variant_SideScrolling/Gameplay",
			"PCombat/Variant_SideScrolling/Interfaces",
			"PCombat/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
