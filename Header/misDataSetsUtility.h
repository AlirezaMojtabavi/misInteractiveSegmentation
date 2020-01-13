#pragma once

#ifndef  misDataSetsUtility_H
#define  misDataSetsUtility_H

#include "ICoordinateSystemCorrelationManager.h"
#include "misVolumeDataDependensies.h"
#include "misPrimaeryNeededHeader.h"
#include "misRegistrationResult.h"
#include "misResultCode.h"
#include "misStrctDataSets.h"
#include "misTypes.h"
#include "IPackagePlanRelFactory.h"
#include "misCompeletePolyDataDependensiesStrct.h"

typedef std::vector<misCompeletePolyDataDependensiesStrct> PolyDataDependencyListTypes;

//remove  this class due to coupling created by this class
typedef  std::vector<std::shared_ptr<parcast::IPackagePlanRel>> PlanDataListDependencyTypedef;

class    misDataSetsUtility
{  
public:
 
	std::string  makeCompleteName(std::string Name, std::string modality, std::string NumberOfImages);
	static   bool     FindDuplicatedImageInPackage     (ImageDependencyListTypes imageDependencyList, misUID  imageUID) ;
	static   bool     FindDuplicatedPolyDataInPackage  (PolyDataDependencyListTypes * polydataDependencyList  ,misUID  polyDataUID);
 	static   bool     FindDuplicatedPlanDataInPackage  (std::shared_ptr<PlanDataListDependencyTypedef>   plandataDependencyList,  
		misUID  newparrentObjectUID);
};


#endif
