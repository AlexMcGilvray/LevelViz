// Fill out your copyright notice in the Description page of Project Settings.
#include "ArchVizViewerPrivatePCH.h"
#include "VantagePoint.h"

#include "GameFramework/PlayerController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/EngineTypes.h"   


// Sets default values
AVantagePoint::AVantagePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance 
	// if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); 

	if (RootComponent)
	{
		Camera->AttachTo(RootComponent); 
	}
}

// Called when the game starts or when spawned
void AVantagePoint::BeginPlay()
{ 
}

// Called every frame
void AVantagePoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
#if WITH_EDITOR 
	for (auto VantagePoint : LinkedVantagePoints)
	{ 
		if (VantagePoint && GetWorld()->WorldType == EWorldType::Editor)
		{
			DrawDebugLine(this->GetWorld(), this->GetActorLocation(), VantagePoint->GetActorLocation(), FColor::Red, false, -1.0f, '\000', 5.0f);
		}
	}
#endif
}

bool AVantagePoint::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AVantagePoint::TransitionToThisCamera(float blendTime)
{
	auto controller = this->GetWorld()->GetFirstPlayerController();
	controller->SetViewTargetWithBlend(this, blendTime);
	//controller->GetFocalLocation()
}
#if WITH_EDITOR
void AVantagePoint::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	AActor::PostEditChangeProperty(PropertyChangedEvent);

	for (auto VantagePoint : LinkedVantagePoints)
	{ 
		if (VantagePoint)
		{
			VantagePoint->LinkedVantagePoints.AddUnique(this);
		}
	}

	//this is the rough brute force method where we add back each camera link then remove this camera from any other camera links
	for (TActorIterator<AVantagePoint> Itr(GetWorld()); Itr; ++Itr)
	{
		bool VantagePointExistsInLinkedVantagePoints = LinkedVantagePoints.Contains(*Itr) && Itr->LinkedVantagePoints.Contains(this);
		//we only care about every vantage point other than this one
		if (*Itr == this)
			continue;

		//we never want to be able to link to ourselves
		if (LinkedVantagePoints.Contains(this))
		{
			LinkedVantagePoints.Remove(this);
		}
		
		if (!VantagePointExistsInLinkedVantagePoints)
		{
			Itr->LinkedVantagePoints.Remove(this);
		} 
	} 
	//TODO handle the allocation etc for this elsewhere. Maybe in the view manager. Too hard to keep track of here.
	for (auto VantagePoint : LinkedVantagePoints)
	{
		/*	if (VantagePoint)
			{
				auto Transition = NewObject<UVantagePointTransition>(UVantagePointTransition::StaticClass());
				if (Transition)
				{
					Transition->VantagePointLeft = this;
					Transition->VantagePointRight = VantagePoint;
					VantagePointTransitions.Add(Transition);
				}

			}*/
	}
}
#endif