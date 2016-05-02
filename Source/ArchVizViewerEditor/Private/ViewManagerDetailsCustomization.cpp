// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchVizViewerEditor.h"
#include "ViewManagerDetailsCustomization.h" 
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailLayoutBuilder.h"
#include "ViewManager.h"

#define LOCTEXT_NAMESPACE "ViewManagerDetails"

FViewManagerDetailsCustomization::FViewManagerDetailsCustomization()
{
}
FViewManagerDetailsCustomization::~FViewManagerDetailsCustomization()
{

}

TSharedRef<IDetailCustomization> FViewManagerDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FViewManagerDetailsCustomization);
}

void FViewManagerDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	ObjectsBeingCustomized.Empty();
	DetailBuilder.GetObjectsBeingCustomized(/*out*/ ObjectsBeingCustomized);
	IDetailCategoryBuilder& ViewManagerCategory = DetailBuilder.EditCategory("Arch Viz Debugging", FText::GetEmpty());
	ViewManagerCategory.SetCategoryVisibility(true);  

	{
		ViewManagerCategory.AddCustomRow(LOCTEXT("Plan View", "Plan View"))
			.WholeRowContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.0f, 0.0f)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Text(LOCTEXT("Launch Editor", "Launch Editor"))
			.ToolTipText(LOCTEXT("LaunchEditor_ToolTip", "Launches the ViewManager standalone editor."))
			.OnClicked(this, &FViewManagerDetailsCustomization::LaunchViewManagerEditor)
			]
			];
	}
}

//TODO : This wont work because we can never select the objects without de-selecting this object. Gotta find another way
FReply FViewManagerDetailsCustomization::LaunchViewManagerEditor()
{
	
	//auto Window = SNew(SWindow)
	//	.Title(LOCTEXT("WindowTitle", "ArchVizTools"))
	//	.ClientSize(FVector2D(200.0f, 600.0f))
	//	.SupportsMaximize(true)
	//	.SupportsMinimize(false)
	//	[
	//		SNew(SVerticalBox)
	//		+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	.Padding(2.0f, 0.0f)
	//	.VAlign(VAlign_Top)
	//	.HAlign(HAlign_Left)
	//	[
	//		SNew(SButton)
	//		.Text(LOCTEXT("Add selected objects", "Add selected objects"))
	//	.ToolTipText(LOCTEXT("MergeSprites_Tooltip", "Merges all selected sprite components into entries on a single grouped sprite component"))
	//	.OnClicked(this, &FViewManagerDetailsCustomization::AddSelectedObjects)
	//	] + SVerticalBox::Slot().AutoHeight()
	//	.Padding(2.0f, 0.0f)
	//	.VAlign(VAlign_Top)
	//	.HAlign(HAlign_Left)
	//	[
	//		SNew(SButton)
	//		.Text(LOCTEXT("Remove selected objects", "Remove selected objects"))
	//	.ToolTipText(LOCTEXT("MergeSprites_Tooltip", "Merges all selected sprite components into entries on a single grouped sprite component"))
	//	.OnClicked(this, &FViewManagerDetailsCustomization::RemoveSelectedObjects)
	//	] + SVerticalBox::Slot().AutoHeight()
	//	.Padding(2.0f, 0.0f)
	//	.VAlign(VAlign_Top)
	//	.HAlign(HAlign_Left)
	//	[
	//		SNew(SButton)
	//		.Text(LOCTEXT("Turn on outline rendering", "Turn on outline rendering"))
	//	.ToolTipText(LOCTEXT("MergeSprites_Tooltip4", "Merges all selected sprite components into entries on a single grouped sprite component"))
	//	.OnClicked(this, &FViewManagerDetailsCustomization::TurnOnOutlineRendering)
	//	] + SVerticalBox::Slot().AutoHeight()
	//	.Padding(2.0f, 0.0f)
	//	.VAlign(VAlign_Top)
	//	.HAlign(HAlign_Left)
	//	[
	//		SNew(SButton)
	//		.Text(LOCTEXT("Turn off outline rendering", "Turn off outline rendering"))
	//	.ToolTipText(LOCTEXT("MergeSprites_Tooltip4", "Merges all selected sprite components into entries on a single grouped sprite component"))
	//	.OnClicked(this, &FViewManagerDetailsCustomization::TurnOffOutlineRendering)
	//	]
	//	];;

	//FSlateApplication::Get().AddWindow(Window);

	static FName ArchVizEditorModuleName("ArchVizViewerEditor");
	FArchVizViewerEditorModule& ArchVizEditorModule = FModuleManager::GetModuleChecked<FArchVizViewerEditorModule>(ArchVizEditorModuleName);
	ArchVizEditorModule.ViewManagerEditor.LaunchViewManagerEditor();

	return FReply::Handled();
}


//TODO : Refactor these 2 functions since they only differ in one line. Maybe pass in a lamda for that line and keep everything else the same
FReply FViewManagerDetailsCustomization::AddSelectedObjects()
{
	AViewManager * ViewManager = CachedViewManager; 
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);
	 
	if (ViewManager)
	{
		for (auto SelectedObject : StrongObjects)
		{
			auto SelectedObjectAsStaticMesh = Cast<AStaticMeshActor>(SelectedObject);
			if (SelectedObjectAsStaticMesh)
			{
				ViewManager->PlanElements.Add(SelectedObjectAsStaticMesh);
			}
		}
	}
	return FReply::Handled();
}

FReply FViewManagerDetailsCustomization::RemoveSelectedObjects()
{
	AViewManager * ViewManager = CachedViewManager;
	int DebugLoopCount = 0;
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);
	
	if (ViewManager)
	{
		for (auto SelectedObject : StrongObjects)
		{
			auto SelectedObjectAsStaticMesh = Cast<AStaticMeshActor>(SelectedObject);
			if (SelectedObjectAsStaticMesh)
			{
				ViewManager->PlanElements.Remove(SelectedObjectAsStaticMesh);
			}
		}
	}
	return FReply::Handled();
}

FReply FViewManagerDetailsCustomization::TurnOnOutlineRendering()
{ 
	UE_LOG(LogTemp, Warning, TEXT("FViewManagerDetailsCustomization::TurnOnOutlineRendering()"));
	AViewManager * ViewManager = CachedViewManager;
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);
	
	if (!ViewManager)
	{
		return FReply::Handled();
	}

	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		auto CurrentObject = *Itr;
		bool FoundOutlineObject = false;
		for (auto OutlineObject : ViewManager->PlanElements)
		{
			if (OutlineObject == CurrentObject)
			{
				FoundOutlineObject = true;
			}
		}
		if (!FoundOutlineObject)
		{ 
			CurrentObject->SetIsTemporarilyHiddenInEditor(true);
			UE_LOG(LogTemp, Warning, TEXT("Hiding object"));
		}
	}
	for (auto OutlineObject : ViewManager->PlanElements)
	{
		OutlineObject->SetIsTemporarilyHiddenInEditor(false);
		auto RenderComponent = OutlineObject->GetRootPrimitiveComponent();
		if (RenderComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding to custom depth pass"));
			RenderComponent->bRenderCustomDepth = true;
			RenderComponent->bRenderInMainPass = false;
		} 
	}

	UPostProcessComponent * PostProcessComponent = ViewManager->FindComponentByClass<UPostProcessComponent>();
	if (!PostProcessComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Somehow got a null PostProcessComponent from view manager."));
		return FReply::Handled();
	}
	PostProcessComponent->bEnabled = true;
	 
	return FReply::Handled();
}

FReply FViewManagerDetailsCustomization::TurnOffOutlineRendering()
{
	UE_LOG(LogTemp, Warning, TEXT("FViewManagerDetailsCustomization::TurnOffOutlineRendering()"));
	AViewManager * ViewManager = CachedViewManager;
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);

	if (!ViewManager)
	{
		return FReply::Handled();
	}

	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		auto CurrentObject = *Itr;  
		if (CurrentObject)
		{
			CurrentObject->SetIsTemporarilyHiddenInEditor(false);
		} 
	}
	for (auto OutlineObject : ViewManager->PlanElements)
	{
		OutlineObject->SetIsTemporarilyHiddenInEditor(false);
		auto RenderComponent = OutlineObject->GetRootPrimitiveComponent();
		if (RenderComponent)
		{
			RenderComponent->bRenderCustomDepth = 0;
			RenderComponent->bRenderInMainPass = true;
		}
	}

	UPostProcessComponent * PostProcessComponent = ViewManager->FindComponentByClass<UPostProcessComponent>(); 
	if (!PostProcessComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Somehow got a null PostProcessComponent from view manager."));
		return FReply::Handled();
	} 
	PostProcessComponent->bEnabled = false;

	return FReply::Handled();
}



void FViewManagerDetailsCustomization::DebugPrintAllComponentsToLog(AActor * ActorToQuery)
{
	UE_LOG(LogTemp, Warning, TEXT("FViewManagerDetailsCustomization::DebugPrintAllComponentsToLog(AActor * ActorToQuery)"));
	auto Components = ActorToQuery->GetComponents();
	for (auto CurrentComponent : Components)
	{
		FString ComponentName = CurrentComponent->GetFullName();
		UE_LOG(LogTemp, Warning, TEXT("Component : %s"), *ComponentName);
	}
}

AViewManager * FViewManagerDetailsCustomization::GetViewManager()
{
	AViewManager * ViewManager = nullptr;
	int DebugLoopCount = 0;
	//TODO - This is bad. We want to cache a reference to the view manager rather than iterate over everything every time this function is called.
	//for (TActorIterator<AViewManager> Itr(GetWorld()); Itr; ++Itr)
	for (TObjectIterator<AViewManager> Itr; Itr; ++Itr)
	{
		DebugLoopCount++;
		ViewManager = *Itr; 
	}
	//There should only ever be one view manager in a scene
	check(DebugLoopCount == 1 && ViewManager);
	if (ViewManager)
	{
		return ViewManager;
	}
	else
	{
		return nullptr;
	}
}
