// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"

 
/**
 * 
 */
class ARCHVIZVIEWEREDITOR_API FVantagePointDetailsCustomization : public IDetailCustomization
{
public:
	FVantagePointDetailsCustomization();
	~FVantagePointDetailsCustomization();

	static TSharedRef<IDetailCustomization> MakeInstance();
		/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	//TSharedRef<SWidget> OnGenerateElementForVantagePoints(TSharedRef<IPropertyHandle> ElementProperty, int ElementIndex);
};
