// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LFGame : ModuleRules
{
	public LFGame(ReadOnlyTargetRules Target) : base(Target)
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
			"LFGame",
			"LFGame/Variant_Platforming",
			"LFGame/Variant_Platforming/Animation",
			"LFGame/Variant_Combat",
			"LFGame/Variant_Combat/AI",
			"LFGame/Variant_Combat/Animation",
			"LFGame/Variant_Combat/Gameplay",
			"LFGame/Variant_Combat/Interfaces",
			"LFGame/Variant_Combat/UI",
			"LFGame/Variant_SideScrolling",
			"LFGame/Variant_SideScrolling/AI",
			"LFGame/Variant_SideScrolling/Gameplay",
			"LFGame/Variant_SideScrolling/Interfaces",
			"LFGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
