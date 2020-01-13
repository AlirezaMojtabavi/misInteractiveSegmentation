#pragma once

#include "INavigationViewersNView.h"
#include "misPlanData.h"
#include "misStringTools.h"
#include "IPackageDataAdapter.h"

using Vector3DLandmarkViewer = std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp>;
MOCK_BASE_CLASS(MockNavigationViewersNView, INavigationViewersNView)
{
	MOCK_NON_CONST_METHOD(ClearAnnotationDetailFromViewer, 0, void());
	MOCK_NON_CONST_METHOD(RefreshCurrentPackage, 0, void());
	MOCK_NON_CONST_METHOD(Active, 1, void(bool val));
	MOCK_NON_CONST_METHOD(Freeze, 0, void());
	MOCK_NON_CONST_METHOD(Unfreeze, 0, void());
	MOCK_NON_CONST_METHOD(ResetLandMarks, 1, void(misLandmarkType lndType));
	MOCK_NON_CONST_METHOD(ResetAllLandMarks, 0, void());
	MOCK_NON_CONST_METHOD(SetRealTimeMode, 1, void(bool val));
	MOCK_NON_CONST_METHOD(SetDentalSurgeryType, 1, void(DentalSurgeryType surgeryType));
	MOCK_NON_CONST_METHOD(SetObliqueFlag, 1, void(bool isObiquw));
	MOCK_NON_CONST_METHOD(SetCroppingDirection, 3, void(misCroppingDirectionInVR croppingDirection, const double* center, bool isobliqe));
	MOCK_NON_CONST_METHOD(AddLandmark, 4, void(unsigned int landmarkIndex, itk::Point<double, 3> landmark, misLandmarkType landmarkType,
		LANDMARKLABLETYPE lableType));
	MOCK_NON_CONST_METHOD(Reset2DZoom, 0, void());
	MOCK_NON_CONST_METHOD(ClipVolumeWithObliquePlane, 2, void(const double* planeNormal, const double* center));
	MOCK_NON_CONST_METHOD(SetWidgetLineWeight, 1, void(double weight));
	MOCK_NON_CONST_METHOD(ChangeWidgetType, 1, void(misCursorType cursorType));
	MOCK_NON_CONST_METHOD(SetObliqueChangedObserver, 1, void(std::weak_ptr<IObliqueChanged> observer));
	MOCK_NON_CONST_METHOD(SetPlanIsSelectedInViewerObserver, 1, void(std::weak_ptr<IPlanSelectedInViewer> observer));
	MOCK_NON_CONST_METHOD(UpdateViewingPropertiesTexture, 2, void(bool DisplayErasedObjectStatus, misColorStruct ColorStr));
	MOCK_NON_CONST_METHOD(ReleaseResource, 0, void());
	MOCK_NON_CONST_METHOD(Render, 0, void());
	MOCK_NON_CONST_METHOD(SetAnnotationDetailToViewer, 0, void());
	MOCK_NON_CONST_METHOD(ClippingOff, 0, void());
	MOCK_NON_CONST_METHOD(VolumeLandmarkCaptureDisable, 0, void());
	MOCK_NON_CONST_METHOD(ImageLandmarkCaptureDisable, 0, void());
	MOCK_NON_CONST_METHOD(ImageLandmarkUpdateEnable, 2, void(misLandmarkType pLandmarkType, int index));
	MOCK_NON_CONST_METHOD(ImageLandmarkUpdateDisable, 0, void());
	MOCK_NON_CONST_METHOD(ModifyBiopsyPoint, 1, void(misLandmarkType landmarkType));
	MOCK_NON_CONST_METHOD(GetCurrentZoomPercentage, 0, int());
	MOCK_NON_CONST_METHOD(GetCurrentZoomProportion, 0, double());
	MOCK_NON_CONST_METHOD(ImageLandmarkCaptureEnable, 3, void(misLandmarkType pLandmarkType, int index = -1,
		LANDMARKLABLETYPE lableType));
	MOCK_NON_CONST_METHOD(ShowPackage, 2, void(std::shared_ptr<ISimpleDataPackage> , bool  ), ShowPackage_1);
	MOCK_NON_CONST_METHOD(ShowPackageImages, 2, void(std::shared_ptr<ISimpleDataPackage>, bool ) );
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(UpdateLandmarks, 1, void(misLandmarkInfoStruct &lndStr));
	MOCK_CONST_METHOD(GetViewerByType, 1, std::shared_ptr<IVolumeRenderer>(misViewerTypeDirection type));
	MOCK_NON_CONST_METHOD(SetExternalEventViewer, 1, void(std::function<void(itk::Object *caller, const itk::EventObject& pEvent)> val));
	MOCK_CONST_METHOD(GetAllViewers, 0, std::vector<std::shared_ptr<I3DViewer>>());
	MOCK_NON_CONST_METHOD(SetImagePlanePosition, 1, void(const double pos[3]));
	MOCK_NON_CONST_METHOD(ApplyWindowlevel, 2, void(misUID imageUID, misWindowLevelStr winLevStr));
	MOCK_NON_CONST_METHOD(Get2DViewers, 0, std::vector<std::shared_ptr<IVolumeSlicer>>());
	MOCK_NON_CONST_METHOD(GetCurrentPosition, 0, parcast::Point<double>(void));
	MOCK_NON_CONST_METHOD(GetCurrentWindowLevel, 1, misWindowLevelStr(misUID imageUID));
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void(misUID imageUID, misColorStruct Color), SetColorValueToTextureidentifer2);
	MOCK_NON_CONST_METHOD(SetTransformMatrix, 1, void(vtkMatrix4x4* transform));
	MOCK_NON_CONST_METHOD(SetImageColor, 2, void(std::vector<misUID> UIDs, misColorStruct imageColor));
	MOCK_NON_CONST_METHOD(GetImageColor, 1, misColorStruct(std::vector<misUID> UIDs));
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void(misUID imageUID, float val), SetOpacityValueToTextureIdentifier2);
	MOCK_NON_CONST_METHOD(Get3DViewers, 0, std::vector<std::shared_ptr<IVolume3DRenderer>>());
	MOCK_CONST_METHOD(GetAllLandMarkViewers, 0, std::vector<std::shared_ptr<IVolumeRenderer>>());
 	MOCK_NON_CONST_METHOD(UpdateViewerROI, 1, void(misROI roi));
	MOCK_NON_CONST_METHOD(ResetROI, 1, void(misROI roi), signature1);
	MOCK_NON_CONST_METHOD(ResetROI, 0, void(), signature2);
	MOCK_NON_CONST_METHOD(UpdateViewerWithImage, 1, void(std::shared_ptr<IImage> image));
	MOCK_NON_CONST_METHOD(VolumeLandmarkCaptureEnable, 3, void(misLandmarkType pLandmarkType, int index = -1, LANDMARKLABLETYPE lableType = NUMERICALLANDMARK));
	MOCK_NON_CONST_METHOD(ShowLandmarks, 0, void());
	MOCK_NON_CONST_METHOD(GetVolumePackageViewer, 0, std::shared_ptr<IPackage3DDataRenderingAdapter>());
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 1, void(std::shared_ptr<ISimpleDataPackage> package));
	MOCK_NON_CONST_METHOD(UpdatePanoramicCurve, 0, void());
	MOCK_NON_CONST_METHOD(GetGroupViewerSetting, 0, std::shared_ptr<IGroupViewerSetting>());
	MOCK_CONST_METHOD(GetPanoramicCoordinateConverter, 0, std::shared_ptr<IPanoramicCoordinatesConverter>());
	MOCK_NON_CONST_METHOD(Add3dRepresentation, 1, void(std::shared_ptr<misRepresentation> PSurfaceRep));
	MOCK_NON_CONST_METHOD(HideLandmarks, 1, void(TypeOfViewer typeOfviewer));
	MOCK_NON_CONST_METHOD(InteractionCapturedFlagOn, 0, void());
	MOCK_NON_CONST_METHOD(InteractionCapturedFlagOff, 0, void());
	MOCK_NON_CONST_METHOD(InvalidateLandmark, 1, void(int index));
	MOCK_NON_CONST_METHOD(ModifyCurrentSelectedLandmark, 2, bool(int landmarkIndex, misLandmarkType landmarkType));
	MOCK_NON_CONST_METHOD(Remove3dRepresentation, 1, void(std::shared_ptr<misRepresentation> PSurfaceRep));
	MOCK_NON_CONST_METHOD(SetSceneReferenceCoordinateSystem, 2, void(size_t viewerIndex, const misUID& coordSysUid), SetSceneReferenceCoordinateSystem_1);
	MOCK_NON_CONST_METHOD(ResetCamera, 0, void());
	MOCK_NON_CONST_METHOD(ResetMeasurment, 0, void());
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(ResetViewerToSimpleImages, 0, void());
	MOCK_NON_CONST_METHOD(SetRoiWidgetActivation, 2, void(const double* roi, bool activation));
	MOCK_NON_CONST_METHOD(ChangeViewerToMultipleImages, 0, void());
	MOCK_NON_CONST_METHOD(SetOrientation, 1, void(IMAGEORIENTATION newOrientation));
	MOCK_NON_CONST_METHOD(SetGroupViewerSetting, 1, void(std::shared_ptr<IGroupViewerSetting> pSettingStr));
	MOCK_NON_CONST_METHOD(ShowPlan, 1, void(std::shared_ptr< parcast::IPackagePlanRel>));
	MOCK_CONST_METHOD(GetRenderingToolExtension, 0, Vector3DLandmarkViewer());
	MOCK_CONST_METHOD(HasObserver, 1, bool(const itk::EventObject & event));
	MOCK_NON_CONST_METHOD(AddObserver, 2, unsigned long(const itk::EventObject & event, itk::Command *command));
	MOCK_NON_CONST_METHOD(InvokeEvent, 1, void(const itk::EventObject& event));
	MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double));
	MOCK_NON_CONST_METHOD(Add2DViewer, 2,void(std::shared_ptr<IPackage2DDataRenderingAdapter>, std::shared_ptr<Iwindows>));
	MOCK_NON_CONST_METHOD(Add3DViewer, 2, void(std::shared_ptr<IPackage3DDataRenderingAdapter>, std::shared_ptr<Iwindows>));
	MOCK_NON_CONST_METHOD(SetVisibilityValueToTexture, 2, void (misUID, bool));
	MOCK_CONST_METHOD(GetAllPackageViewers, 0, std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> () );
	MOCK_NON_CONST_METHOD(SetVisiblityOfColorMap,2,  void (misPlaneEnum , bool ) );
	MOCK_NON_CONST_METHOD(SetColorMapTransFuncID, 2,  void (misPlaneEnum , std::shared_ptr<TransFuncIntensity> ));
	MOCK_NON_CONST_METHOD(SetDefaultVisibilityMap, 1, void (std::vector<std::map<misPlaneEnum, bool>> map) );
	MOCK_NON_CONST_METHOD(ShowVolumes, 1, int (VolumeDataDependencyListTypes ) );
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void(misPlaneEnum , misDoubleColorStruct), SetColorValueToTextureidentifer1);
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void(misPlaneEnum , float ), SetOpacityValueToTextureIdentifier1);
	MOCK_NON_CONST_METHOD(ClearViewers, 0, void() );
	MOCK_NON_CONST_METHOD(GetAllWindow, 0, std::vector<std::shared_ptr<Iwindows>> () );
	MOCK_NON_CONST_METHOD(WarnFlyZone, 1,  void (const std::vector<std::vector<PropertiesOfPixelInImageStr>>& ));
	MOCK_NON_CONST_METHOD(UpdateSliderInGUI, 0, void() );
	MOCK_NON_CONST_METHOD(SetVolumeViewingType, 1, void(misVolumeViewingTypes volumeViewingType));
	MOCK_NON_CONST_METHOD(ShowVolume, 1, void(std::shared_ptr<IVolumeDataDependency> volumeProp));
	MOCK_NON_CONST_METHOD(UpdateColormap, 1, void(std::shared_ptr<IVolumeDataDependency> volumeProp));
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 2, void(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<ISimpleDataPackage> newPackage), UpdateRepresentationTransforms_1);
	MOCK_NON_CONST_METHOD(UpdateRepresentationTransforms, 0, void(), UpdateRepresentationTransforms_2);
	MOCK_NON_CONST_METHOD(ReleaseImageResources, 0, void());
	MOCK_NON_CONST_METHOD(SetWidgetType, 1, void(misCursorType pWidgetType));
	MOCK_NON_CONST_METHOD(GetViewer, 0, std::shared_ptr<IVolumeRenderer>());
	MOCK_NON_CONST_METHOD(SetSceneReferenceCoordinateSystem, 2, void(const std::string& coordSysUid,
		std::shared_ptr<ISimpleDataPackage> package), SetSceneReferenceCoordinateSystem_2);
	MOCK_NON_CONST_METHOD(SetDentalSpecialViewsEnable, 2, void(std::shared_ptr<IVolumeRenderer> viewer, bool enabled));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 2, void(std::shared_ptr<const IPanoramicCoordinatesConverter>
		coordinateConverter, std::shared_ptr<IVolumeRenderer> viewer));
	MOCK_NON_CONST_METHOD(ShowSegmentedObjects, 3, int(const misSegmentationSetting&, ImageContainedPolydataDependencyListTypes, double minOpacity));
	MOCK_NON_CONST_METHOD(ShowPlans, 2, int(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef> rels));
	MOCK_NON_CONST_METHOD(UpdatePosition, 1, void(parcast::Point<double, 3> position));
	MOCK_NON_CONST_METHOD(SetVisibilityOfSegmentedImage, 2, void(misUID imageuid, bool val));
	MOCK_NON_CONST_METHOD(UpdatePlaneVisibilities, 1,  void (std::vector<std::map<misPlaneEnum, bool>>));
	MOCK_NON_CONST_METHOD(ShowPackage, 7, void(std::shared_ptr<ISimpleDataPackage>, const misVisualizationSetting&,
		const misSegmentationSetting&, double minOpacity, bool resetZoom, misCursorType pWidgetType,
		std::map<misPlaneEnum, bool> pPlaneVisible), ShowPackage_2);
	MOCK_NON_CONST_METHOD(ChangeViewerToSameImages, 0,  void () );

};