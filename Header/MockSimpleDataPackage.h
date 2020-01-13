#pragma once

#include "ISimpleDataPackage.h"
#include "misCompeletePolyDataDependensiesStrct.h"

MOCK_BASE_CLASS(MockSimpleDataPackage, ISimpleDataPackage)
{
	MOCK_NON_CONST_METHOD(SetObjectUID, 1, void(const misUID& dataUID));
	MOCK_CONST_METHOD(GetObjectUID, 0, misUID());
	MOCK_NON_CONST_METHOD(SetName, 1, void(std::string name));
	MOCK_CONST_METHOD(GetName, 0, std::string());
	MOCK_CONST_METHOD(GetObjectType, 0, MisObjectType());
	MOCK_NON_CONST_METHOD(GetImageDataProperties, 1, misShortImageViewingStrct(misUID objectUID));
	MOCK_NON_CONST_METHOD(Get3DModelDataProperties, 2, misShort3DModelViewingStrct(misUID objectContainerUID, misUID objectUID));
	MOCK_NON_CONST_METHOD(GetPlanDataProperties, 1, misShortPlanningViewingStruct(misUID objectUID));
	MOCK_NON_CONST_METHOD(SetObjectVisibility, 4, void(misUID objectContainerUID, misUID objectUID, bool isVisible,
		misPresentationDimension presentationDim));
	MOCK_NON_CONST_METHOD(SetObjectOpacity, 3, void(misUID objectContainerUID, misUID objectUID, double opacity));
	MOCK_NON_CONST_METHOD(SetObjectColor, 2, misResultCode::ResultIds(misUID objectUID, misColorStruct color));
	MOCK_NON_CONST_METHOD(SetImagedataOpacity, 2, misResultCode::ResultIds(misUID objectUID, double visible));
	MOCK_CONST_METHOD(GetNumberOfImages, 0, int());
	MOCK_NON_CONST_METHOD(GetNumberOf3DModels, 0, int());
	MOCK_CONST_METHOD(GetNumberOfPlanes, 0, size_t());
	MOCK_CONST_METHOD(GetMainImage, 0, std::shared_ptr<IImage>());
	MOCK_CONST_METHOD(GetImages, 0, std::vector<std::shared_ptr<IImage>>());
	MOCK_CONST_METHOD(GetMainImageUID, 0, misUID());
	MOCK_CONST_METHOD(GetMainImageProperites, 0, std::shared_ptr<ICompeleteImageDependencies>());
	MOCK_NON_CONST_METHOD(SetImageContainedPolyData, 1, misResultCode::ResultIds(misUID mianImageUID));
	MOCK_NON_CONST_METHOD(AddNextImageContainedPolydata, 2, misResultCode::ResultIds(misUID   pImageData, misUID parentImageUID), AddNextImageContainedPolydata_sig1);
	MOCK_NON_CONST_METHOD(AddNextImageContainedPolydata, 1, misResultCode::ResultIds(std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> imageDataDependency), AddNextImageContainedPolydata_sig2);
	MOCK_NON_CONST_METHOD(AddNextPolydata, 2, misResultCode::ResultIds(misUID   pPolydata, misUID parrentImageUID), AddNextPolydata_sig1);
	MOCK_NON_CONST_METHOD(AddNextPolydata, 1, misResultCode::ResultIds(misCompeletePolyDataDependensiesStrct     polydataDependency), AddNextPolydata_sig2);
	MOCK_NON_CONST_METHOD(AddNextVolumedata, 3, misResultCode::ResultIds(misUID   pVolumedata, misUID parrentImageUID, misObjectVisibilityMap visibleParts), AddNextVolumedata_sig1);
	MOCK_NON_CONST_METHOD(AddNextVolumedata, 1, misResultCode::ResultIds(std::shared_ptr < IVolumeDataDependency> volumedataDependency), AddNextVolumedata_sig2);
	MOCK_NON_CONST_METHOD(AddNextSegmentedData, 3, misResultCode::ResultIds(misUID objectContainer, misUID parentImageUID, 	misObjectVisibilityMap));
	MOCK_NON_CONST_METHOD(UpdateVolumedata, 2, misResultCode::ResultIds(misUID pVolumedata, misObjectVisibilityMap visibleParts));
	MOCK_CONST_METHOD(GetImageDataDependencies, 0, ImageDependencyListTypes(void));
	MOCK_CONST_METHOD(GetImageContainedPolydataDependencies, 0, ImageContainedPolydataDependencyListTypes(void));
	MOCK_CONST_METHOD(GetPolyDataDependencies, 0, PolyDataDependencyListTypes(void));
	MOCK_CONST_METHOD(GetVolumeDataDependencies, 0, VolumeDataDependencyListTypes(void));
	MOCK_NON_CONST_METHOD(GetPlanDataDependencies, 0, std::shared_ptr<PlanDataListDependencyTypedef>(void));
	MOCK_NON_CONST_METHOD(GetLandMarkPointer, 0, misLandMarkBase*(void));
	MOCK_NON_CONST_METHOD(GetLandMarkPoints, 0, misLandmarkListTypdef(void));
	MOCK_NON_CONST_METHOD(SetLandMarkPoints, 1, bool(misLandmarkListTypdef landMarkPoints));
	MOCK_NON_CONST_METHOD(DeleteAllLandmarks, 0, void());
	MOCK_NON_CONST_METHOD(Delete3DModel, 2, bool(misUID objectContainerUID, misUID ObjectUID));
	MOCK_NON_CONST_METHOD(DeleteVolumedata, 1, misResultCode::ResultIds(misUID volumeDataUID));
	MOCK_NON_CONST_METHOD(DeleteAllVolumedatas, 0, void());
	MOCK_NON_CONST_METHOD(UpdateImageSDataPointer, 1, misResultCode::ResultIds(ImageListTypedef       imagePointerList));
	MOCK_NON_CONST_METHOD(UpdateImageContainedPolyDataSDataPointer, 1, misResultCode::ResultIds(ImageContainedPolyDataListTypedef imagePointerList));
	MOCK_NON_CONST_METHOD(UpdateVolumeSDataPointer, 1, misResultCode::ResultIds(VolumeDataListTypedef*  volumeDataPointerList));
	MOCK_NON_CONST_METHOD(DeleteSegmentedObject, 2, misResultCode::ResultIds(misUID segmentedObjUID, misUID objectContainerUID));
	MOCK_NON_CONST_METHOD(DeleteRenderingObject, 2, misResultCode::ResultIds(misUID renderedUID, misUID volumedataUID));
	MOCK_NON_CONST_METHOD(FindObjectType, 1, MisObjectType(misUID objectUID));
	MOCK_NON_CONST_METHOD(ResetPackage, 0, misResultCode::ResultIds());
	MOCK_NON_CONST_METHOD(InvisibleAllPlanDatas, 0, misResultCode::ResultIds());
	MOCK_NON_CONST_METHOD(SetMarginAlaram, 3, misResultCode::ResultIds(misUID containerUID, misUID SegmentedObjectUID, bool val));
	MOCK_NON_CONST_METHOD(ShowMarginRegion, 3, misResultCode::ResultIds(misUID containerUID, misUID SegmentedObjectUID, bool val));
	MOCK_NON_CONST_METHOD(DeletePlanData, 1, misResultCode::ResultIds(misUID planDataUID));
	MOCK_CONST_METHOD(GetCSCorrelationManager, 0, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >());
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(SetImageToRelatedImageDataDependancy, 1, void(std::shared_ptr<IImage> image));
	MOCK_NON_CONST_METHOD(SetImageDataDependencies, 1, misResultCode::ResultIds(const ImageDependencyListTypes& imageDataSDependencies));
	MOCK_NON_CONST_METHOD(SetImageContainedPolyDataDependencies, 1, misResultCode::ResultIds(ImageContainedPolydataDependencyListTypes imageDataSDependencies));
	MOCK_NON_CONST_METHOD(SetVolumeDataDependencies, 1, void(VolumeDataDependencyListTypes volumeDataSDependencies));
	MOCK_NON_CONST_METHOD(SetPolyDataDependencies, 1, misResultCode::ResultIds(PolyDataDependencyListTypes*  polydataSDependencies));
	MOCK_CONST_METHOD(GetParametricSpline, 0, PointListType());
	MOCK_NON_CONST_METHOD(SetParametricSpline, 1, void(const PointListType& val));
	MOCK_NON_CONST_METHOD(CreateVolumeFromImage, 3, void(std::shared_ptr<IImage> image, double threshold, misApplicationType appType));
	MOCK_NON_CONST_METHOD(CreateTemporaryVolumeDependency, 3, std::shared_ptr<IVolumeDataDependency>(double volumeThreshold,
		std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType), CreateTemporaryVolumeDependency_sig1);
	MOCK_NON_CONST_METHOD(CreateTemporaryVolumeDependency, 3, std::shared_ptr<IVolumeDataDependency>(double volumeThreshold,
		std::shared_ptr<IImage> image, misApplicationType appType), CreateTemporaryVolumeDependency_sig2);
	MOCK_NON_CONST_METHOD(ExtractPlansListFromPackage, 0, std::shared_ptr<PlanDataListTypedef>());
	MOCK_NON_CONST_METHOD(GetFlyzoneStatus, 1, std::string(const double* position));
	MOCK_NON_CONST_METHOD(Modified, 0, void());
	MOCK_NON_CONST_METHOD(SetImagedataVisibility, 2, void(misUID objectUID, bool visible));
};