#pragma once
#include "IVolumeCropping.h"
#include "INavigationViewersNView.h"

class misVolumeCropping final : public IVolumeCropping
{
public:
	misVolumeCropping(std::weak_ptr<INavigationViewersNView> groupViewer, misCroppingDirectionInVR);
	void CropVolume(bool oblique, const double* planeNormal, const double* center) override;
	void UpdateCroppingDirection(void) override;
	misCroppingDirectionInVR GetCroppingDirection() const override;
	void SetCroppingDirection(misCroppingDirectionInVR val) override;
	void SetGroupViewer(std::weak_ptr<INavigationViewersNView> groupViewer) override;
private:
	void UpdateViewBasedOnCroppingDirection(void);

	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	misCroppingDirectionInVR m_CroppingDirection;


};


