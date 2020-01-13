#include "StdAfx.h"
#include "misDataSetsUtility.h"

#include "misDataSetManager.h"
#include "misPlanData.h"
#include "misStringTools.h"
#include "misTransform.h"
#include "misVertebraScrewPlanData.h"
#include "IPackagePlanRel.h"

using std::for_each;
using std::string;
using std::vector;

 

string  misDataSetsUtility::makeCompleteName(string Name, string modality, string NumberOfImages)
{
	string CompleteName;

	CompleteName.append(Name);
	CompleteName.append(" ");
	CompleteName.append("<");
	CompleteName.append(modality);
	CompleteName.append("::");
	CompleteName.append(NumberOfImages);
	CompleteName.append(">");

   return CompleteName;
}


bool misDataSetsUtility::FindDuplicatedImageInPackage(ImageDependencyListTypes imageDependencyList ,misUID imageUID )
{	
	misUID containedUID;
	for(auto imageDependency:imageDependencyList)
	{
		containedUID = imageDependency->GetObjectUID();
		if (! imageUID.compare(containedUID))
           return true;
	}
	return false;
}

bool misDataSetsUtility::FindDuplicatedPolyDataInPackage(PolyDataDependencyListTypes*  polydataDependencyList,misUID  polyDataUID)
{	
	PolyDataDependencyListTypes::iterator  listIterator;
	misUID                                 containedUID;

	for(listIterator=polydataDependencyList->begin(); listIterator!=polydataDependencyList->end(); listIterator++)
	{
		containedUID = listIterator->objectUID;


		if (! polyDataUID.compare(containedUID))
		{
			// there is duplicated Image
			return true;
		}
	}
	return false;
}

 

bool misDataSetsUtility::FindDuplicatedPlanDataInPackage(std::shared_ptr<PlanDataListDependencyTypedef>   plandataDependencyList,
	misUID newparrentObjectUID)
{
	for (auto plan : *plandataDependencyList)
	{
		auto containedUID = plan->GetPlanEntity()->GetUID();
		if (newparrentObjectUID == containedUID)
		{
			return true;
		}
	}
	return false;
	 
}

