#pragma once
#include "INavigationViewersNView.h"
#include "misImageToPatientLandmarkBasedRegistation.h"
#include "IAddFixedLandmarks.h"

class misAddFixedLandmarks : public IAddFixedLandmarks
{
public:
	misAddFixedLandmarks(std::shared_ptr<INavigationViewersNView> gviewer, 
		std::shared_ptr<IImageToPatientLandmarkBasedRegistation>  landmarkRefrence);
	void AddLandmarks(misLandmarkListTypdef landmarks) override;
private:

	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation>  m_pLandmarkList;
};