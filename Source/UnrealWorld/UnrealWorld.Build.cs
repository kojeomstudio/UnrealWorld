// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealWorld : ModuleRules
{
	public UnrealWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"TestPlugin",
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"Slate",
			"SlateCore",
			"PakFile",
			"HTTP" ,
			"Json",
			"JsonUtilities",
            "AIModule",
            "NavigationSystem"
        });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
