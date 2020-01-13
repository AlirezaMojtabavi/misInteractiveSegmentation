#pragma once
#include "IViewingTypeColormapSelector.h"

MOCK_BASE_CLASS(MockViewingTypeColormapSelector,IViewingTypeColormapSelector)
{
	MOCK_NON_CONST_METHOD(SelectVolumeType, 1, void(misVolumeViewingTypes volumeType));
	MOCK_NON_CONST_METHOD(SetCurrentModelType, 1, void(mis3DModelTypes val));
	MOCK_NON_CONST_METHOD(SetCurrentVolumeThreshold, 1, void(double val));
	MOCK_NON_CONST_METHOD(SetCurrentPackage, 1, void(std::shared_ptr<ISimpleDataPackage>));
	MOCK_CONST_METHOD(GetCurrentVolumeType, 0, misVolumeViewingTypes());
	MOCK_CONST_METHOD(GetCurrentModelType, 0, mis3DModelTypes());
	MOCK_NON_CONST_METHOD(ModifyCurrentSelectedLandmark, 2, void(int landmarkIndex, misVolumeViewingTypes volumeType));
	MOCK_CONST_METHOD(GetCurrentVolumeThreshold, 0, double());
	MOCK_CONST_METHOD(GetCurrentThreshold, 0, double());
	MOCK_CONST_METHOD(GetValidObjectThresholdRange, 0, boost::optional<misObjectRangeStr>());
	MOCK_CONST_METHOD(GetLandmarkTypeOfCurrentVolume, 0, misLandmarkType());
	MOCK_NON_CONST_METHOD(ShowVolume, 0, void());
};
