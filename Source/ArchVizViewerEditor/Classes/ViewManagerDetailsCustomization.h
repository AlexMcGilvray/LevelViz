// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "IDetailCustomization.h"

 
/**
 * 
 */
class ARCHVIZVIEWEREDITOR_API FViewManagerDetailsCustomization : public IDetailCustomization
{
public:
	FViewManagerDetailsCustomization();
	~FViewManagerDetailsCustomization();


	static TSharedRef<IDetailCustomization> MakeInstance();
	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized; 

	FReply AddSelectedObjects();
	FReply RemoveSelectedObjects(); 
	FReply TurnOnOutlineRendering();
	FReply TurnOffOutlineRendering();
	FReply LaunchViewManagerEditor();


	// Util function for finding all attached components to the actor parameter
	void DebugPrintAllComponentsToLog(AActor * ActorToQuery);


	private:
		class AViewManager * GetViewManager();
		class AViewManager * CachedViewManager;
};


 