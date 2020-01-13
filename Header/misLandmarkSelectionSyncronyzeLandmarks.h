#pragma once
#include "IlandamrkSelectionSyncronizeLandamrks.h"
#include "INavigationViewersNView.h"
#include "IImageToPatientLandmarkBasedRegistation.h"

class mislandamrkSelectionSyncronizeLandamrks : public IlandamrkSelectionSyncronizeLandamrks
{
public:
	mislandamrkSelectionSyncronizeLandamrks(std::shared_ptr<INavigationViewersNView> grouViewer);
	void SyncroizeLandmarks(std::shared_ptr<IImageToPatientLandmarkBasedRegistation>  landmarkList,
	                        std::shared_ptr<ISimpleDataPackage> package) override;
private:
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
 };


