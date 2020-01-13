#include "stdafx.h"
#include "misPlaneVisibilityUpdater.h"


 
misPlaneVisibilityUpdater::misPlaneVisibilityUpdater(std::shared_ptr<I2DRepresetation> imagePlane,
	std::map<misPlaneEnum, bool> fixedVisibiltyMap)
	:m_ImagePlane(imagePlane), 
m_FixedPlanVisibilityMap(fixedVisibiltyMap)
{
}

misPlaneVisibilityUpdater::~misPlaneVisibilityUpdater()
{
}

void misPlaneVisibilityUpdater::UpdatePlaneVisibilty(std::map<misPlaneEnum, bool> pPlaneVisible)
{
	m_ImagePlane->SetFixedVisibiltyPlane(pPlaneVisible);
}

void misPlaneVisibilityUpdater::SetImagePlane(std::shared_ptr<I2DRepresetation> imagePlane)
{
	m_ImagePlane = imagePlane;
}

void misPlaneVisibilityUpdater::SetFixedVisibiltyPlane(std::map<misPlaneEnum, bool> planes)
{
	m_FixedPlanVisibilityMap = planes;
}
