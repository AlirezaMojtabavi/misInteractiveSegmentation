#pragma once
#include "ISimpleDataPackage.h"
 #include "IImageToPatientLandmarkBasedRegistation.h"

class IlandamrkSelectionSyncronizeLandamrks
{
public:
	virtual ~IlandamrkSelectionSyncronizeLandamrks() = default;
	virtual void SyncroizeLandmarks(std::shared_ptr<IImageToPatientLandmarkBasedRegistation>  landmarkList,
	                                std::shared_ptr<ISimpleDataPackage> package) = 0;
};
