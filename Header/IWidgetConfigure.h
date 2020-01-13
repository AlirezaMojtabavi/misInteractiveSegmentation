#pragma once
#include "misPlaneContrast.h"
#include "IImage.h"

// The IWidgetConfigure is responsible for configuring wigth with provided image
class IWidgetConfigure
{
public:
	virtual void PlaceWidgetatCenter(misPlaneEnum planeIndex, std::shared_ptr<IImage> pMisImage) = 0;
};
