#pragma once
class IPlaneVisibilityUpdater
{
public:
	virtual ~IPlaneVisibilityUpdater() = default;
	virtual void UpdatePlaneVisibilty(std::map<misPlaneEnum, bool> pPlaneVisible) = 0;
	virtual void SetImagePlane(std::shared_ptr<I2DRepresetation> imagePlane) = 0;
	virtual void SetFixedVisibiltyPlane(std::map<misPlaneEnum, bool> planes) = 0;
};
