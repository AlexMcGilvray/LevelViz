

#pragma once

#include "GameFramework/GameMode.h"
#include "ArchVizViewerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZVIEWER_API AArchVizViewerGameMode : public AGameMode
{
	GENERATED_BODY()
public:

	AArchVizViewerGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
