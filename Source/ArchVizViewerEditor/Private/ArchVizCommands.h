// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 *  Boilerplat code for setting up all the actions this plugin performcs as commands. Currently it's not implemented because it's 
 *  either overkill or the actions the editor does are not really undoable/mutable actions.
 */
class FArchVizCommands : public TCommands<FArchVizCommands>
{
public:
	FArchVizCommands()
		: TCommands<FArchVizCommands>(
			TEXT("ArchVizCommands"), // Context name for fast lookup
			NSLOCTEXT("Contexts", "ArchVizEditor", "ArchViz Editor"), // Localized context name for displaying
			NAME_None, // Parent
			TEXT("SomeStyleNameThatsRequiredForSomeReason")
			//FPaperStyle::Get()->GetStyleSetName() // Icon Style Set
			)
	{
	}

	// TCommand<> interface
	virtual void RegisterCommands() override;
	// End of TCommand<> interface

public:
	TSharedPtr<FUICommandInfo> TogglePlanView; 
	TSharedPtr<FUICommandInfo> AddSelectedObjectsToPlanView;
	TSharedPtr<FUICommandInfo> RemoveSelectedObjectsToPlanView;
	TSharedPtr<FUICommandInfo> ToggleCameraLinkVisibilityInEditor;
};


 