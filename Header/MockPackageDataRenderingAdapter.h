#pragma once

#include "IPackageDataRenderingAdapter.h"

MOCK_BASE_CLASS(MockPackageDataRenderingAdapter, IPackageDataRenderingAdapter)
{
	MOCK_NON_CONST_METHOD(SetVolumeViewingType, 1, void(misVolumeViewingTypes volumeViewingType));
	MOCK_NON_CONST_METHOD(ShowPackage, 7, void(std::shared_ptr<ISimpleDataPackage>, const misVisualizationSetting&,
		const misSegmentationSetting&, double minOpacity, bool resetZoom, misCursorType pWidgetType,
		std::map<misPlaneEnum, bool> pPlaneVisible));
	MOCK_NON_CONST_METHOD(ShowVolume, 1, void(std::shared_ptr<IVolumeDataDependency> volumeProp));
	MOCK_NON_CONST_METHOD(UpdateColormap, 1, void(std::shared_ptr<IVolumeDataDependency> volumeProp));
	MOCK_NON_CONST_METHOD(ShowVolumes, 1, int(VolumeDataDependencyListTypes NewVolumeDataDependencies));
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 2, void(std::shared_ptr<IVolumeRenderer> , std::shared_ptr<ISimpleDataPackage> ), update_1);
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 0, void(void), update_2);
	MOCK_NON_CONST_METHOD(ReleaseImageResources, 0, void());
	MOCK_NON_CONST_METHOD(SetWidgetType, 1, void(misCursorType pWidgetType));
	MOCK_NON_CONST_METHOD(GetViewer, 0, std::shared_ptr<IVolumeRenderer>());
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(SetSceneReferenceCoordinateSystem, 2, void(const std::string& , std::shared_ptr<ISimpleDataPackage> ));
	MOCK_NON_CONST_METHOD(SetDentalSpecialViewsEnable, 2, void(std::shared_ptr<IVolumeRenderer> viewer, bool enabled));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 2, void(std::shared_ptr<const IPanoramicCoordinatesConverter>
		, std::shared_ptr<IVolumeRenderer> ));
	MOCK_NON_CONST_METHOD(ShowSegmentedObjects, 3, int(const misSegmentationSetting&, ImageContainedPolydataDependencyListTypes, double minOpacity));
	MOCK_NON_CONST_METHOD(ShowPlan, 1, void(std::shared_ptr< parcast::IPackagePlanRel> rel));
	MOCK_NON_CONST_METHOD(ShowPlans, 2, int(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef> rels));
	MOCK_NON_CONST_METHOD(SetVisiblityOfColorMap, 2, void(misPlaneEnum planeIndex, bool val));
	MOCK_NON_CONST_METHOD(SetColorMapTransFuncID, 2, void(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val));
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void(misPlaneEnum , misDoubleColorStruct ), SetColorValue_1);
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void(misPlaneEnum planeIndex, float opacityValue), SetColorValue_2);
	MOCK_NON_CONST_METHOD(UpdatePosition, 1, void(parcast::Point<double, 3> position));
	MOCK_NON_CONST_METHOD(SetVisibilityOfSegmentedImage, 2,  void (misUID , bool ));

};

