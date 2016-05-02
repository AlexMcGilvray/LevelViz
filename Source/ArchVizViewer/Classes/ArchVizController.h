// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Array.h"
#include "ArchVizController.generated.h"

class AVantagePoint;

/**
 * 
 */
UCLASS()
class ARCHVIZVIEWER_API AArchVizController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	AArchVizController(const FObjectInitializer& ObjectInitializer);

#pragma region UI Controller
public:
	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> MainUIAsset;

	// Variable to hold the widget After Creating it.
	UUserWidget* UI;
#pragma endregion
};
