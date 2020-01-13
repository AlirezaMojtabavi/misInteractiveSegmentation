#pragma once
#include "INavigationViewersNView.h"
#include "misObjectRangeStr.h"

class IViewingTypeColormapSelector
{
public:
	virtual ~IViewingTypeColormapSelector() = default;
	virtual void SelectVolumeType(misVolumeViewingTypes volumeType) = 0;
	virtual void SetCurrentModelType(mis3DModelTypes val) = 0;
	virtual void SetCurrentVolumeThreshold(double val) = 0;
	virtual misVolumeViewingTypes GetCurrentVolumeType() const = 0;
	virtual mis3DModelTypes GetCurrentModelType() const = 0;
	virtual void ModifyCurrentSelectedLandmark(int landmarkIndex, misVolumeViewingTypes volumeType) = 0;
	virtual double GetCurrentVolumeThreshold() const = 0;
	virtual double GetCurrentThreshold() const = 0;
	virtual boost::optional<misObjectRangeStr> GetValidObjectThresholdRange() const =0;
	virtual misLandmarkType GetLandmarkTypeOfCurrentVolume() const = 0;
	virtual void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage>) = 0;
	virtual void ShowVolume() = 0;
};
