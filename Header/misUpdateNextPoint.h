#pragma once
#include "IUpdateNextPoint.h"
#include "IValidLandmarksEnumerator.h"
#include "IImageToPatientLandmarkBasedRegistation.h"

class misUpdateNextPoint : public IUpdateNextPoint
{
public:
	misUpdateNextPoint(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> landmarkList,
	                   std::shared_ptr<IValidLandmarksEnumerator> validLandmarksEnumerator,
	                   std::shared_ptr<INavigationViewersNView> groupViewer);
	int Update(int& currentSelectedLandmarkIndex, misLandmarkType lndType,
	           bool& setRegistrationPointRequestSent) override;
private:
	std::shared_ptr<IValidLandmarksEnumerator> m_ValidLandmarksEnumerator;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_pLandmarkList;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
};

