// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchVizViewerEditor.h"
#include "ViewManagerEditor.h"
#include "ViewManager.h"


#define LOCTEXT_NAMESPACE "ViewManagerDetails"
// Sets default values for this component's properties
FViewManagerEditor::FViewManagerEditor()
{
 
}

TArray<AStaticMeshActor *> FViewManagerEditor::GetSelectedStaticMeshes()
{
	TArray<AStaticMeshActor*> SelectedMeshes; 
	for (TObjectIterator<AStaticMeshActor> Itr; Itr; ++Itr)
	{
		auto CurrentActor = *Itr;
		if (CurrentActor->IsSelected())
		{
			SelectedMeshes.Add(CurrentActor);
		}
	}
	return SelectedMeshes;
}


FReply FViewManagerEditor::AddSelectedObjects()
{
	AViewManager * ViewManager = CachedViewManager;
	auto SelectedMeshes = GetSelectedStaticMeshes(); 

	if (ViewManager)
	{
		for (auto SelectedMesh : SelectedMeshes)
		{ 
			ViewManager->PlanElements.Add(SelectedMesh);
		}
	}
	return FReply::Handled();
}

FReply FViewManagerEditor::RemoveSelectedObjects()
{
	AViewManager * ViewManager = CachedViewManager;
	int DebugLoopCount = 0;
	auto SelectedMeshes = GetSelectedStaticMeshes();

	if (ViewManager)
	{
		for (auto SelectedMesh : SelectedMeshes)
		{
			ViewManager->PlanElements.Remove(SelectedMesh);
		}
	}
	return FReply::Handled();
}

FReply FViewManagerEditor::TurnOnOutlineRendering()
{
	UE_LOG(LogTemp, Warning, TEXT("FViewManagerDetailsCustomization::TurnOnOutlineRendering()"));
	AViewManager * ViewManager = CachedViewManager; 

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
		if (OutlineObject == nullptr)
		{
			break;
		}
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

FReply FViewManagerEditor::TurnOffOutlineRendering()
{
	UE_LOG(LogTemp, Warning, TEXT("FViewManagerDetailsCustomization::TurnOffOutlineRendering()"));
	AViewManager * ViewManager = CachedViewManager;

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

void FViewManagerEditor::LaunchViewManagerEditor()
{
	CachedViewManager = GetViewManager();
	auto Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "ArchVizTools"))
		.ClientSize(FVector2D(200.0f, 600.0f))
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
		.OnClicked_Raw(this, &FViewManagerEditor::AddSelectedObjects)
		] + SVerticalBox::Slot().AutoHeight()
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		[
			SNew(SButton)
			.Text(LOCTEXT("Remove selected objects", "Remove selected objects"))
		.ToolTipText(LOCTEXT("MergeSprites_Tooltip", "Merges all selected sprite components into entries on a single grouped sprite component"))
		.OnClicked_Raw(this, &FViewManagerEditor::RemoveSelectedObjects)
		] + SVerticalBox::Slot().AutoHeight()
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		[
			SNew(SButton)
			.Text(LOCTEXT("Turn on outline rendering", "Turn on outline rendering"))
		.ToolTipText(LOCTEXT("MergeSprites_Tooltip4", "Merges all selected sprite components into entries on a single grouped sprite component"))
		.OnClicked_Raw(this, &FViewManagerEditor::TurnOnOutlineRendering)
		] + SVerticalBox::Slot().AutoHeight()
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		[
			SNew(SButton)
			.Text(LOCTEXT("Turn off outline rendering", "Turn off outline rendering"))
		.ToolTipText(LOCTEXT("MergeSprites_Tooltip4", "Merges all selected sprite components into entries on a single grouped sprite component"))
		.OnClicked_Raw(this, &FViewManagerEditor::TurnOffOutlineRendering)
		]
		];;

	FSlateApplication::Get().AddWindow(Window);
	
}

AViewManager * FViewManagerEditor::GetViewManager()
{

	AViewManager * ViewManager = nullptr;
	int DebugLoopCount = 0; 
	//for (TObjectIterator<AViewManager> Itr; Itr; ++Itr)
	//{
	for (TActorIterator<AViewManager> Itr(GEditor->GetEditorWorldContext().World()); Itr; ++Itr)
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
