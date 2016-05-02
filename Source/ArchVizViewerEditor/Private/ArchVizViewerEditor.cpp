#include "ArchVizViewerEditor.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "VantagePointDetailsCustomization.h"
#include "ViewManagerDetailsCustomization.h"
#include "LevelEditor.h"

IMPLEMENT_GAME_MODULE(FArchVizViewerEditorModule, ArchVizViewerEditor);

DEFINE_LOG_CATEGORY(ArchVizViewerEditor)

#define LOCTEXT_NAMESPACE "ArchVizViewerEditor"

void SetupX()
{
	auto Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "ArchVizTools"))
		.ClientSize(FVector2D(1000.0f, 600.0f))
		.SupportsMaximize(true)
		.SupportsMinimize(false)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Text(LOCTEXT("Add selected objects", "Add selected objects"))
			.ToolTipText(LOCTEXT("MergeSprites_Tooltip", "Merges all selected sprite components into entries on a single grouped sprite component"))
			//.OnClicked(this, &FViewManagerDetailsCustomization::TurnOnOutlineRendering)
			] + SVerticalBox::Slot().AutoHeight()
			.Padding(2.0f, 0.0f)
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Text(LOCTEXT("Add selected objectsXXX", "Add selected objects2"))
				.ToolTipText(LOCTEXT("MergeSprites_Tooltip2", "Merges all selected sprite components into entries on a single grouped sprite component"))
				//.OnClicked(this, &FViewManagerDetailsCustomization::TurnOnOutlineRendering)
			] + SVerticalBox::Slot().AutoHeight()
				.Padding(2.0f, 0.0f)
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Text(LOCTEXT("Add selected objectsXXXX", "Add selected objects3"))
				.ToolTipText(LOCTEXT("MergeSprites_Tooltip3", "Merges all selected sprite components into entries on a single grouped sprite component"))
				//.OnClicked(this, &FViewManagerDetailsCustomization::TurnOnOutlineRendering)
			] + SVerticalBox::Slot().AutoHeight()
				.Padding(2.0f, 0.0f)
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Text(LOCTEXT("Add selected objectsXXXXX", "Add selected objects4"))
				.ToolTipText(LOCTEXT("MergeSprites_Tooltip4", "Merges all selected sprite components into entries on a single grouped sprite component"))
				//.OnClicked(this, &FViewManagerDetailsCustomization::TurnOnOutlineRendering)
			]
		];;

	FSlateApplication::Get().AddWindow(Window);
}

void SetupEditorWindow(FToolBarBuilder& ToolbarBuilder)
{
	//FUIAction ActionX(FExecuteAction::CreateStatic(&SetupX));  
	//ToolbarBuilder.AddToolBarButton(ActionX,TEXT("xxx"),TEXT("XXXX")); 
	//ToolbarBuilder.AddToolBarButton(FXXX::Get().RefreshTests); 
}


void FArchVizViewerEditorModule::StartupModule()
{
	UE_LOG(ArchVizViewerEditor, Warning, TEXT("ArchVizViewerEditor: Log Started"));
	static FName PropertyEditor("PropertyEditor");
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
	PropertyModule.RegisterCustomClassLayout("VantagePoint", FOnGetDetailCustomizationInstance::CreateStatic(&FVantagePointDetailsCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout("ViewManager", FOnGetDetailCustomizationInstance::CreateStatic(&FViewManagerDetailsCustomization::MakeInstance));

	BindCommands();
}

void FArchVizViewerEditorModule::ShutdownModule()
{
	UE_LOG(ArchVizViewerEditor, Warning, TEXT("ArchVizViewerEditor: Log Ended"));
}

//@TODO consider whether or not it makes sense to convert the actions this plugin does to commands. 
void FArchVizViewerEditorModule::BindCommands()
{
	//const FArchVizCommands& Commands = FArchVizCommands::Get();
}

#undef LOCTEXT_NAMESPACE