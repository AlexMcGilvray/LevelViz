// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h" 
#include "VantagePoint.generated.h"


class UCameraComponent;
class AViewManager;
class USceneCaptureComponent2D;
class UVantagePointTransition;

UCLASS()
class ARCHVIZVIEWER_API AVantagePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVantagePoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override; 

	// Override to force this to tick even when only the viewports are rendering
	virtual bool ShouldTickIfViewportsOnly() const override;

	// Makes a call to cause the camera blend from whereever it is to this vatnage point
	UFUNCTION(BlueprintCallable, Category = VantagePoint)
	void TransitionToThisCamera(float blendTime = 3.0f);

	// Child camera component. This is primarily here for the benefit of the designer so they can see a camera view while manipulating the 
	// point's transform
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VantagePoint, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	
	// Array of all linked vantage points
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = VantagePoint, meta = (AllowPrivateAccess = "true"))
	TArray<AVantagePoint*> LinkedVantagePoints;
 
	// Name of this vantage point. This is what will show up in the UI.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VantagePoint)
	FText VantageName;

	// Reference to the ViewManager
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VantagePoint, meta = (AllowPrivateAccess = "true"))
	AViewManager * ViewManagerParent;

#if WITH_EDITOR
	// So we can do bi-directional links between camera and save the designer from having to do that manually
	virtual void PostEditChangeProperty( FPropertyChangedEvent & PropertyChangedEvent ) override;
#endif
};
