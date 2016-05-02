#include "ArchVizViewerEditor.h"
#include "VantagePointDetailsCustomization.h" 
#include "VantagePoint.h" 
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailLayoutBuilder.h"

#define LOCTEXT_NAMESPACE "VantagePointDetails"

FVantagePointDetailsCustomization::FVantagePointDetailsCustomization()
{
}

FVantagePointDetailsCustomization::~FVantagePointDetailsCustomization()
{
}

TSharedRef<IDetailCustomization> FVantagePointDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FVantagePointDetailsCustomization);
}

void FVantagePointDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	UE_LOG(ArchVizViewerEditor, Warning, TEXT("ArchVizViewerEditor: Trying to customize details"));

	IDetailCategoryBuilder& VantagePointCategory = DetailBuilder.EditCategory("Vantage Point", FText::GetEmpty()); 
	VantagePointCategory.SetCategoryVisibility(true); 
	auto LinkedCameras = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AVantagePoint, LinkedVantagePoints));

	ObjectsBeingCustomized.Empty();
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
 
}
 