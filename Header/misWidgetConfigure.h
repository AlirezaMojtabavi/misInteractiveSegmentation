#pragma once
#include "IWidgetConfigure.h"
#include "IVolumeRenderer.h"

class misWidgetConfigure :public IWidgetConfigure
{
public:
	misWidgetConfigure(std::shared_ptr<IVolumeRenderer> viewer);
	void PlaceWidgetatCenter(misPlaneEnum planeIndex, std::shared_ptr<IImage> pMisImage) override;
private:
	std::shared_ptr<IVolumeRenderer> m_viewer;
};

