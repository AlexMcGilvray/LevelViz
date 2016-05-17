// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ViewManager.generated.h"

// forward declare
class AVantagePoint;
class UUserWidget;

//delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetReachedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTransitionBeginDelegate);

UCLASS()
class ARCHVIZVIEWER_API AViewManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaTime) override;

	// Attempts to transition from the current camera position to the target vantage point's view
	UFUNCTION(BlueprintCallable, Category = ViewManagerTargetting)
	void TransitionToVantagePoint(AVantagePoint * TargetVantagePoint);

	// Fire when a transition to a vantage point is completed 
	UPROPERTY(BlueprintAssignable, Category = ViewManagerTargetting)
	FOnTargetReachedDelegate OnTargetReached;

	// Fires when a transition to a vantage point begins
	UPROPERTY(BlueprintAssignable, Category = ViewManagerTargetting)
	FOnTransitionBeginDelegate OnTransitionBegin;
	
	// The current vantage point that our camera is at
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ViewManagerTargetting)
	AVantagePoint * CurrentVantagePoint;

	// Deprecated, required for old UI which used render targets for UI elements
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ViewManagerTargetting, meta = (AllowPrivateAccess = "true"))
	TArray<USceneCaptureComponent2D *> SceneCaptureTargets;

	// The geometry that contributes to the plan view
	// @TODO accept other types of actors besides static meshes like BSP brushes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ViewManagerPlans)
	TArray<AActor*> PlanElements;

	// Kicks off the camera to transition into plan view
	UFUNCTION(BlueprintCallable, Category = ViewManagerPlans)
	void TransitionIntoPlanView();

	// The post process component we use for rendering the plan view as well as determining the size of the ortho matrix we use for the plan view
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ViewManagerPlans)
	UPostProcessComponent * PostProcessVolume;

	// List of all vantage points in the world
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ViewManagerPlans)
	TArray<AVantagePoint *> VantagePoints;

	// Whether or not we are in plan view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ViewManagerPlans)
	bool IsInPlanView;

private:
	// Change render state to outline rendering
	void TurnOnOutlineRendering();

	// Change render state to standard mode
	void TurnOffOutlineRendering();

	// Switches the active camera to orthographic projection and makes adjustments for the topdown plan view
	void CameraSwitchToTopDownOrtho();

	// Switches the active camera to perspective projection
	void CameraSwitchToStandardPerspective();

	// Internal function to kickoff the camera blend to topdown view
	UFUNCTION()
	void BlendToTopDownView(); 

	// Child actor root component used as a transform target for topdown view camera blends
	UPROPERTY()
	USceneComponent * TopViewAnchorRootComponent;

	// Child actor used as a transform target for topdown view camera blends
	UPROPERTY()
	AActor * TopViewAnchor;

	// If this is non-null then we have a target and are actively approaching it every tick
	AVantagePoint * TargetVantagePoint;

	//not currently used
	TUniquePtr<FTimeline> VantagePointTransitionTimeline;

#pragma region Transition timer data
	// NOTE: Ideally I would not use timers and would rely on callbacks from the camera blend sysetm but there are no such callbacks. Ideally I would modify the engine
	// source to support this but that would break the plugin from working with standard distributions of the unreal engine. 
	// @TODO look into adding callback support for camera blends to the engine and if it's viable submit a pull request 

	// Whether or not the transition is active and it's accompanying timer counting down
	bool IsTransitionTimerCountingDown;

	// Whether or not we are transitioning into plan view
	bool IsInTransitionToPlanView;

	// Current value of the transition timer
	float TransitionTimer;
#pragma endregion

	// DEPRECATED : used for previous UI which used render targets
	const int NUM_SCENE_CAPTURE_TARGETS = 4;
};
