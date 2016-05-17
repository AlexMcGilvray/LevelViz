// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
  
class FViewManagerEditor 
{ 

public:	
	// Sets default values for this component's properties
	FViewManagerEditor();
		
	FReply AddSelectedObjects();
	FReply RemoveSelectedObjects();
	FReply TurnOnOutlineRendering();
	FReply TurnOffOutlineRendering();

	void LaunchViewManagerEditor();

	class AViewManager * GetViewManager();
	class AViewManager * CachedViewManager;

	TArray<class AActor *> GetSelectedStaticMeshes();

};
