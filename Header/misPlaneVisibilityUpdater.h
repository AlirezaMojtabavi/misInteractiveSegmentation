#pragma once
#include <I2DRepresentation.h>
#include "IPlaneVisibilityUpdater.h"

class misPlaneVisibilityUpdater : public IPlaneVisibilityUpdater
{
public:
	misPlaneVisibilityUpdater(std::shared_ptr<I2DRepresetation> imagePlane,
		std::map<misPlaneEnum, bool> fixedVisibiltyMap);
 	~misPlaneVisibilityUpdater();

	void UpdatePlaneVisibilty(std::map<misPlaneEnum, bool> pPlaneVisible) override;
	void SetImagePlane(std::shared_ptr<I2DRepresetation> imagePlane) override;
	void SetFixedVisibiltyPlane(std::map<misPlaneEnum, bool> planes) override;

	private:
		std::shared_ptr<I2DRepresetation> m_ImagePlane;
		std::map<misPlaneEnum, bool> m_FixedPlanVisibilityMap;
};

