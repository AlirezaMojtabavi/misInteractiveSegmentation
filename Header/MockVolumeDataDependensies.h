#pragma once

#include "IVolumeDataDependency.h"

MOCK_BASE_CLASS(MockVolumeDataDependensies, IVolumeDataDependency)
{
	MOCK_CONST_METHOD(GetVolume, 0, std::shared_ptr<IVolumeData>());
	MOCK_NON_CONST_METHOD(SetVolume, 1, void(std::shared_ptr<IVolumeData> val));
	MOCK_CONST_METHOD(GetImage, 0, std::shared_ptr<IImage>());
	MOCK_NON_CONST_METHOD(SetImage, 1, void(std::shared_ptr<IImage> image));
	MOCK_NON_CONST_METHOD(SetAllObjectVisibility, 1, void(const misObjectVisibilityMap &val), SetAllObjectVisibility_sig1);
	MOCK_NON_CONST_METHOD(SetAllObjectVisibility, 1, void(bool visibility), SetAllObjectVisibility_sig2);
	MOCK_NON_CONST_METHOD(SetObjectVisibilityProperties, 2, void(const misUID &uid, const mis3DModelObjectOpacityPropertiesStrct &properties));
	MOCK_NON_CONST_METHOD(ClearObjectVisibilities, 0, void());
	MOCK_CONST_METHOD(GetObjectVisibilityProperties, 2, bool(const misUID &uid, mis3DModelObjectOpacityPropertiesStrct& model));
	MOCK_NON_CONST_METHOD(DeleteObjectVisibility, 1, void(misUID uid));
	MOCK_NON_CONST_METHOD(SetObjectVisibility, 3, bool(const misUID &uid, misPresentationDimension whichScene, bool visibility), SetObjectVisibility_sig1);
	MOCK_NON_CONST_METHOD(SetObjectVisibility, 2, bool(const misUID &uid, bool visibility), SetObjectVisibility_sig2);
	MOCK_NON_CONST_METHOD(SetObjectOpacity, 3, bool(const misUID &uid, misPresentationDimension whichScene, double opacity), SetObjectOpacity_sig1);
	MOCK_NON_CONST_METHOD(SetObjectOpacity, 2, bool(const misUID &uid, double opacity), SetObjectOpacity_sig2);
	MOCK_CONST_METHOD(GetAllObjectVisibility, 0, misObjectVisibilityMap());
	MOCK_NON_CONST_METHOD(SetComponentVisiblityByMap, 1, int(misObjectVisibilityMap visibilityMap));
	MOCK_CONST_METHOD(GetVisibilityIn2D, 0, bool());
	MOCK_NON_CONST_METHOD(SetVisibilityIn2D, 1, void(bool val));
	MOCK_CONST_METHOD(GetObjectUID, 0, misUID());
	MOCK_NON_CONST_METHOD(SetObjectUID, 1, void(misUID val));
	MOCK_CONST_METHOD(GetAutomaticallyCreated, 0, bool());
	MOCK_NON_CONST_METHOD(SetAutomaticallyCreated, 1, void(bool val));
	MOCK_NON_CONST_METHOD(GetTransferFunction, 1, std::shared_ptr<TransFuncIntensity>(misPresentationDimension presentationDim), GetTransferFunction_sig1);
	MOCK_NON_CONST_METHOD(SetTransferFunction, 1, void(std::shared_ptr<TransFuncIntensity> transfunction));
	MOCK_CONST_METHOD(GetTransferFunction, 0, std::shared_ptr<TransFuncIntensity>(), GetTransferFunction_sig2);
	MOCK_NON_CONST_METHOD(SetParentImageUID, 1, void(const misUID& uid));
	MOCK_CONST_METHOD(GetParentImageUID, 0, misUID());
};
