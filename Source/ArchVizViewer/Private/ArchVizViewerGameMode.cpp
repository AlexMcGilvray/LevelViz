// Fill out your copyright notice in the Description page of Project Settings.
#include "ArchVizViewerPrivatePCH.h"
#include "ArchVizViewerGameMode.h"  


AArchVizViewerGameMode::AArchVizViewerGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PlayerControllerClass = AArchVizController::StaticClass();

	// One-time initialization

	//bStartPlayersAsSpectators = false;
	//bDelayedStart = false;
	//bNetLoadOnClient = false;
	//PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickGroup = TG_PrePhysics;
	//HUDClass = AHUD::StaticClass();
	//MatchState = MatchState::EnteringMap;
	//bPauseable = true;
	//DefaultPawnClass = ADefaultPawn::StaticClass();
	//SpectatorClass = ASpectatorPawn::StaticClass();
	//ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
	//EngineMessageClass = UEngineMessage::StaticClass();
	//GameStateClass = AGameState::StaticClass();
	//CurrentID = 1;
	//PlayerStateClass = APlayerState::StaticClass();
	//MinRespawnDelay = 1.0f;
	//InactivePlayerStateLifeSpan = 300.f;
}

void AArchVizViewerGameMode::BeginPlay()
{
	Super::BeginPlay();
	

	

}

void AArchVizViewerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	

}
