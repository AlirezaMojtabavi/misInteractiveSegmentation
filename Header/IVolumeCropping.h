#pragma once
#include "misCroppingDirectionInVR.h"
#include "INavigationViewersNView.h"

class IVolumeCropping
{
public:
	virtual void UpdateCroppingDirection(void) = 0;
	virtual void CropVolume(bool oblique, const double* planeNormal, const double* center) = 0;
	virtual misCroppingDirectionInVR GetCroppingDirection() const = 0;
	virtual void SetCroppingDirection(misCroppingDirectionInVR val) = 0;
	virtual void SetGroupViewer(std::weak_ptr<INavigationViewersNView> groupViewer) = 0;

};
