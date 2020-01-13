#pragma once
#include "ICorrelationUpdateViewerLandmarks.h"
#include "misImageToImageLandmarkBasedRegistration.h"

namespace  parcast
{
class CorrelationUpdateViewerLandmarks :
	public parcast::ICorrelationUpdateViewerLandmarks
{
public:
	CorrelationUpdateViewerLandmarks(std::shared_ptr<misImageToImageLandmarkBasedRegistration>, std::shared_ptr<INavigationViewersNView>);
 
	void UpdateViewerLandmarks() override;
private:
	std::shared_ptr<misImageToImageLandmarkBasedRegistration> m_LandmarkBasedFusion;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
};
	
}

