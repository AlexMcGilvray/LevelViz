// Fill out your copyright notice in the Description page of Project Settings.
#include "ArchVizViewerPrivatePCH.h"
#include "HelperBlueprints.h"
#include "Camera/PlayerCameraManager.h"

bool UHelperBlueprints::IsActorInFrontOfCamera(AActor * const Actor, APlayerCameraManager * const Camera)
{
	FVector CameraForwardVector = Camera->GetActorForwardVector();
	FVector ActorDirectionTowardsActor	= Actor->GetActorLocation() - Camera->GetCameraLocation();
	ActorDirectionTowardsActor.Normalize();
	auto DotProduct = FVector::DotProduct(ActorDirectionTowardsActor, CameraForwardVector);
	if (DotProduct < 0.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}

FVector2D UHelperBlueprints::GetClockRotationOfActorRelativeToOtherActor(AActor * const TargetActor, AActor * const Source)
{
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector SourceLocation = Source->GetActorLocation();
	FVector FinalDirection = SourceLocation - TargetLocation;
	FVector SourceForward = Source->GetActorForwardVector();
	FinalDirection.Normalize();
	FinalDirection = FinalDirection.RotateAngleAxis(FMath::RadiansToDegrees(FMath::Atan2(SourceForward.X, SourceForward.Y)), FVector(0, 0, 1));
	return FVector2D(FinalDirection.X, FinalDirection.Y);
}
