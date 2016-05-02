// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchVizViewerEditor.h"
#include "ArchVizCommands.h"
 
#define LOCTEXT_NAMESPACE "ArchViz"

void FArchVizCommands::RegisterCommands()
{
	UI_COMMAND(TogglePlanView, "Toggle Plan View", "XXX", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(AddSelectedObjectsToPlanView, "Add Selected Objects to Plan View", "XXX", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(RemoveSelectedObjectsToPlanView, "Remove Selected Objects from Plan View", "XXXX", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ToggleCameraLinkVisibilityInEditor, "Toggle Camera Link Visibility", "XXXX", EUserInterfaceActionType::ToggleButton, FInputChord());
}

#undef LOCTEXT_NAMESPACE