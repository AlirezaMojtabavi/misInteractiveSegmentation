#pragma once
#include "IPackageDataAdapter.h"

MOCK_BASE_CLASS(MockPackageViewer, IPackageDataRenderingAdapter)
{
	MOCK_NON_CONST_METHOD(SetVolumeViewingType, 1, void(misVolumeViewingTypes));
	MOCK_NON_CONST_METHOD(ShowPackage, 2, void(std::shared_ptr<ISimpleDataPackage>, bool));
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 1, void(std::shared_ptr<ISimpleDataPackage> pPackage))
		MOCK_NON_CONST_METHOD(ReleaseRenderingResources, 0, void());
	MOCK_NON_CONST_METHOD(SetWidgetType, 1, void(misCursorType pWidgetType));
	MOCK_NON_CONST_METHOD(SetPlaneVisibilityStatus, 1, void(std::map<misPlaneEnum, bool> pPlaneVisible));
	MOCK_NON_CONST_METHOD(SetAllPlaneVisible, 0, void());
	MOCK_NON_CONST_METHOD(SetWindowRenderer, 2, void(std::shared_ptr<Iwindows> pWindow, int rendererIndex));
	MOCK_NON_CONST_METHOD(GetViewer, 0, ViewerType(void));
	MOCK_NON_CONST_METHOD(GetCurrentWindowLevel, 1, misWindowLevelStr(misUID imageUID));
	MOCK_NON_CONST_METHOD(ApplyWindowlevel, 2, void(misUID imageUID, misWindowLevelStr winLevStr));
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void(misUID imageUID, misDoubleColorStruct Color));
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void(misUID imageUID, float val));
	MOCK_NON_CONST_METHOD(ModifyVolume, 0, void());
	MOCK_NON_CONST_METHOD(SetOrientation, 1, void(IMAGEORIENTATION newOrientation));
	MOCK_NON_CONST_METHOD(ShowPlan, 1, void(misPlanData* newPlanDataDependencies));
	MOCK_NON_CONST_METHOD(ApplyOffset, 1, void(double offset));
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 0, void(void), Identifie_1);
	MOCK_NON_CONST_METHOD(SetSceneReferenceCoordinateSystem, 1, void(const misUID& coordSysUid));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 1, void(std::shared_ptr<const IPanoramicCoordinatesConverter> ));
	MOCK_NON_CONST_METHOD(SetDentalSpecialViewsEnable, 1, void(bool enabled));
	MOCK_NON_CONST_METHOD(ShowVolumeObjectsIn3Dviewers, 1, void(std::shared_ptr<IVolumeDataDependensies> volumeProp));
};