// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArchVizViewerEditor : ModuleRules
{
	public ArchVizViewerEditor(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG",
            "MainFrame",
            "LevelEditor"});

	
		//Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "ArchVizViewer",
            "SlateCore",
            "PropertyEditor",
            "EditorStyle",
            "UnrealEd",
            "DetailCustomizations"});

		PublicIncludePaths.AddRange(
            new string[]{
                "ArchVizViewerEditor/Public"
            });
 
        PrivateIncludePaths.AddRange(
            new string[] {
			"ArchVizViewerEditor/Private",
		});

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
