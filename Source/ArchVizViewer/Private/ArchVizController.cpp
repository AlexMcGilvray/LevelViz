// Fill out your copyright notice in the Description page of Project Settings.
#include "ArchVizViewerPrivatePCH.h"
#include "ArchVizController.h"
#include "../UMG/Public/Blueprint/UserWidget.h"
#include "ViewManager.h"
#include "Components/ChildActorComponent.h"


AArchVizController::AArchVizController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true; 
	if (RootComponent)
	{
		//ViewManager = Cast<AViewManager>(GetWorld()->SpawnActor(AViewManager::StaticClass())); 
		// We want to drive rotation with ControlRotation regardless of attachment state.
		 
		RootComponent->bAbsoluteRotation = true;
	}
}

void AArchVizController::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(1, 4, FColor::Blue, "Initialized AArchVizController controller");

	if (MainUIAsset) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		UI = CreateWidget<UUserWidget>(this, MainUIAsset);

		// now you can use the widget directly since you have a ref for it.
		// Extra check to  make sure the pointer holds the widget.
		if (UI)
		{
			//let add it to the view port
			UI->AddToViewport();
		}
		//Show the Cursor.
		bShowMouseCursor = true;
	}

}
