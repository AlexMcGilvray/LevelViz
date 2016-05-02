// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperBlueprints.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZVIEWER_API UHelperBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// Use the dot product to determine if an object is fin front or behind a camera
	UFUNCTION(BlueprintCallable, Category = WorldQueries)
	static bool IsActorInFrontOfCamera(AActor * Actor, class APlayerCameraManager * Camera);

	/**
	* This function returns a vector that represents the clock hand rotation of the target relative to the source projected on the xy plane. Similar to 
	* military movies where someone says that the target is at 2 oclock.
	* @param TargetActor The actor who's clock rotation value this function returns
	* @param Source The actor who we are using as the query. This of this as the center of the clock and 12 oclock is it's forward vector in the xy plane
	* @see https://docs.unrealengine.com/latest/INT/Gameplay/Networking/Replication/
	*/
	UFUNCTION(BlueprintCallable, Category = WorldQueries)
	static FVector2D GetClockRotationOfActorRelativeToOtherActor(AActor * const TargetActor, AActor * const Source);
};
