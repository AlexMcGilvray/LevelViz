#pragma once

#include "Engine.h"
#include "ModuleManager.h"
#include "UnrealEd.h"
#include "ViewManagerEditor.h"

DECLARE_LOG_CATEGORY_EXTERN(ArchVizViewerEditor, All, All)

class FArchVizViewerEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	 
	//seems like we dont actually need this
	FViewManagerEditor ViewManagerEditor;

	
	void BindCommands();

};