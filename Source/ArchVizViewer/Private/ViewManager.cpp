// Fill out your copyright notice in the Description page of Project Settings.
#include "ArchVizViewerPrivatePCH.h"
#include "ViewManager.h"
#include "VantagePoint.h"
#include "Components/TimelineComponent.h"
#include "UObjectGlobals.h"

// Sets default values
AViewManager::AViewManager(const FObjectInitializer& ObjectInitializer)
	:VantagePointTransitionTimeline(new FTimeline())
{
	for (int i = 0; i < NUM_SCENE_CAPTURE_TARGETS; ++i)
	{
		auto name = FString::Printf(TEXT("Scene Component %i"), i);
		SceneCaptureTargets.Add(ObjectInitializer.CreateDefaultSubobject<USceneCaptureComponent2D>(this, *name));
	}

	auto BoxRoot = CreateDefaultSubobject<UBoxComponent>( TEXT("Box Root"));
	RootComponent = BoxRoot;
	PostProcessVolume = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Process Volume"));
	PostProcessVolume->AttachParent = RootComponent;
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AViewManager::BeginPlay()
{
	Super::BeginPlay();

	TopViewAnchor = this->GetWorld()->SpawnActor(AActor::StaticClass());
	//TopViewAnchorRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Top View Anchor Root Component"));
	TopViewAnchorRootComponent = NewObject<USceneComponent>(TopViewAnchor, TEXT("Root Component"));
	TopViewAnchor->SetRootComponent(TopViewAnchorRootComponent);

	for (TActorIterator<AVantagePoint> Itr(GetWorld()) ; Itr; ++Itr)
	{
		Itr->ViewManagerParent = this;
		VantagePoints.Add(*Itr);
	} 
	if (VantagePoints.Num() > 0)
	{
		TargetVantagePoint = VantagePoints[0];
	}
	else
	{
		//error - no vantage points in the scene
	}

	TurnOffOutlineRendering();
}

// Called every frame
void AViewManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetVantagePoint)
	{
		TransitionTimer = 3.0f;
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Blue, TEXT("Moving to new target"));
		TargetVantagePoint->TransitionToThisCamera();
		CurrentVantagePoint = TargetVantagePoint;
		
		TargetVantagePoint = nullptr;
		IsTransitionTimerCountingDown = true;
		int i = 0;
		for (auto VantagePoint : CurrentVantagePoint->LinkedVantagePoints)
		{
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Blue, TEXT("Setting scene capture position"));
			if (i < SceneCaptureTargets.Num())
			{
				SceneCaptureTargets[i]->SetWorldTransform(VantagePoint->GetTransform());
			} 
			else break;
			i++;
		}
	} 

	if (IsTransitionTimerCountingDown)
	{
		TransitionTimer -= DeltaTime;
		if (TransitionTimer <= 0)
		{
			IsTransitionTimerCountingDown = false;
			if (IsInTransitionToPlanView)
			{
				TurnOnOutlineRendering();
				CameraSwitchToTopDownOrtho();
				IsInTransitionToPlanView = false;
				IsInPlanView = true;
			}
			OnTargetReached.Broadcast();
		}
	}
} 

void AViewManager::TransitionToVantagePoint(AVantagePoint * TargetVantagePoint)
{
	this->TargetVantagePoint = TargetVantagePoint;
	IsInPlanView = false;
	OnTransitionBegin.Broadcast();
	TurnOffOutlineRendering();
}

void AViewManager::TransitionIntoPlanView()
{
	OnTransitionBegin.Broadcast();
	BlendToTopDownView();
}

void AViewManager::BlendToTopDownView()
{
	auto Controller = this->GetWorld()->GetFirstPlayerController();
	/*auto PostProcessVolumeCenter = PostProcessVolume->Bounds.GetBox().GetCenter();
	auto PostProcessVolumeBoundsMax = PostProcessVolume->Bounds.GetBox().Max; */
	auto TopViewAnchorRotation = RootComponent->GetComponentRotation();
	FVector TopViewAnchorLocation = RootComponent->GetComponentLocation();
	TopViewAnchorLocation.Z += 2450; //@TODO Make this a function of something. Maybe some point where the camera frustum matches the bounding volume...

	TransitionTimer = 3.0f;

	TopViewAnchorRotation.Add(-90.0f, 0.0f, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("Top view location %f %f %f"), TopViewAnchorLocation.X, TopViewAnchorLocation.Y, TopViewAnchorLocation.Z);
	UE_LOG(LogTemp, Warning, TEXT("Top view rotation %f %f %f"), TopViewAnchorRotation.Pitch, TopViewAnchorRotation.Yaw, TopViewAnchorRotation.Roll);

	bool TransformSuccess = TopViewAnchor->SetActorLocation(TopViewAnchorLocation);
	TransformSuccess = TopViewAnchor->SetActorRotation(TopViewAnchorRotation);
	if (!TransformSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not actor set somehow"));
	}
	
	Controller->SetViewTargetWithBlend(TopViewAnchor, TransitionTimer);

	{
		auto TopViewAnchorLocation2 = TopViewAnchor->GetActorLocation();
		auto TopViewAnchorRotation2 = TopViewAnchor->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("Top view location after transform %f %f %f"), TopViewAnchorLocation2.X, TopViewAnchorLocation2.Y, TopViewAnchorLocation2.Z);
		UE_LOG(LogTemp, Warning, TEXT("Top view rotation after transform %f %f %f"), TopViewAnchorRotation2.Pitch, TopViewAnchorRotation2.Yaw, TopViewAnchorRotation2.Roll);
	}

	IsInTransitionToPlanView = true;
	IsTransitionTimerCountingDown = true;
}

void AViewManager::TurnOnOutlineRendering()
{
	PostProcessVolume->bEnabled = true;
	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		auto CurrentObject = *Itr;
		bool FoundOutlineObject = false;
		for (auto OutlineObject : PlanElements)
		{
			if (OutlineObject == CurrentObject)
			{
				FoundOutlineObject = true;
			}
		}
		if (!FoundOutlineObject)
		{
			CurrentObject->SetActorHiddenInGame(true);
		}
	}
	for (auto OutlineObject : PlanElements)
	{
		if (OutlineObject)
		{
			OutlineObject->SetActorHiddenInGame(false);
			auto RenderComponent = OutlineObject->GetRootPrimitiveComponent();
			if (RenderComponent)
			{
				RenderComponent->bRenderCustomDepth = true;
				RenderComponent->bRenderInMainPass = false;
				RenderComponent->MarkRenderStateDirty();
			}
		}
	}
}

void AViewManager::TurnOffOutlineRendering()
{  
	PostProcessVolume->bEnabled = false;
	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		auto CurrentObject = *Itr;
		if (CurrentObject)
		{
			CurrentObject->SetActorHiddenInGame(false); 
		}
	}
	for (auto OutlineObject : PlanElements)
	{
		if (OutlineObject)
		{
			OutlineObject->SetActorHiddenInGame(false);
			auto RenderComponent = OutlineObject->GetRootPrimitiveComponent();
			if (RenderComponent)
			{
				RenderComponent->bRenderCustomDepth = false;
				RenderComponent->bRenderInMainPass = true;
				RenderComponent->MarkRenderStateDirty();
			}
		}
	}
	CameraSwitchToStandardPerspective();
}

void AViewManager::CameraSwitchToTopDownOrtho()
{
	auto Controller = this->GetWorld()->GetFirstPlayerController();
	Controller->PlayerCameraManager->bIsOrthographic = true;
	FVector Origin;
	FVector Extents;
	this->GetActorBounds(false, Origin, Extents);
	auto LargerDimension = FMath::Max(Extents.X, Extents.Y);
	UE_LOG(LogTemp, Warning, TEXT("Post process volume larger dimension size is %f "), LargerDimension);
	Controller->PlayerCameraManager->DefaultOrthoWidth = LargerDimension * 3;
}

void AViewManager::CameraSwitchToStandardPerspective()
{
	auto Controller = this->GetWorld()->GetFirstPlayerController();
	Controller->PlayerCameraManager->bIsOrthographic = false;
}
