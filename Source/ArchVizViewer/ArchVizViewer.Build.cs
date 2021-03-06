// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArchVizViewer : ModuleRules
{
	public ArchVizViewer(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG"});

	
		//Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore"   });

        if (UEBuildConfiguration.bBuildEditor)
        { 
            PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd", "EditorStyle", "PropertyEditor", "DetailCustomizations" });
        }

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        // {
        //		if (UEBuildConfiguration.bCompileSteamOSS == true)
        //		{
        //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //		}
        // }
    }
}
