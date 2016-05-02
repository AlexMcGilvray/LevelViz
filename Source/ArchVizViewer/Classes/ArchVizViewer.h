#pragma once
 
#include "ModuleManager.h"
 
class ArchVizViewerPluginImpl : public IModuleInterface
{
public:
	void StartupModule();
	void ShutdownModule();
};
