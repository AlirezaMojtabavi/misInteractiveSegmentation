#pragma once

#include "INavigationViewersNView.h"
#include "IPanoramicTransformConverter.h"
#include "ISubsequenceLayout.h"
#include "misApplicationSetting.h"
#include "misGroupViewerSetting.h"
#include "misVolumeSlicer.h"
#include "misN4VStateVariable.h"
#include "IPackage2DDataRenderingAdapter.h"
#include "IPackage3DDataRenderingAdapter.h"
#include "IUpdateViewPortToStandard.h"
#include "IUpdateViewPortToOblique.h"


class misGroupViewer : public virtual  INavigationViewersNView
{
public:

	class Injector
	{
	public:
		virtual std::shared_ptr<Iwindows> CreateRenderingWindow();
	};

	typedef itk::MemberCommand<misGroupViewer> ObserverType;

	misGroupViewer(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IGroupViewerSetting> groupViwerSetting,
		std::shared_ptr<Injector> injector = nullptr);
	~misGroupViewer();

	virtual void SetObliqueChangedObserver(std::weak_ptr<IObliqueChanged> observer) override;
	virtual void SetPlanIsSelectedInViewerObserver(std::weak_ptr<IPlanSelectedInViewer> observer) override;
	void SetVolumeViewingType(misVolumeViewingTypes volumeViewingType);
	void SetGroupViewerSetting(std::shared_ptr<IGroupViewerSetting> pSettingStr) override;
	std::shared_ptr<IGroupViewerSetting> GetGroupViewerSetting() override;
	virtual void Add3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep);
	void SetImagePlanePosition(const double pos[3]);
	parcast::Point<double, 3> GetCurrentPosition(void);
	void GetCurrentPosition(double currentPos[3]);
	void Render() override;
	void ResetCamera();
	int GetCurrentZoomPercentage();
	double GetCurrentZoomProportion();
	void ResetMeasurment();
	void ApplyWindowlevel(misUID imageUID, misWindowLevelStr winLevStr);
	void SetColorValueToTexture(misUID imageUID, misColorStruct Color);
	void SetOpacityValueToTexture(misUID imageUID, float val);
	void SetVisibilityValueToTexture(misUID imageUID, bool val) override;
	void UpdateViewingPropertiesTexture(bool DisplayErasedObjectStatus, misColorStruct ColorStr);
	void SetRealTimeMode(bool val);
	void ChangeWidgetType(misCursorType cursorType);
	std::shared_ptr<IPackage3DDataRenderingAdapter> GetVolumePackageViewer() override;
	// Sets the relative weight of the line used in drawing the cursor widget at the center of each of the image viewers.
	void SetWidgetLineWeight(double weight);

	misWindowLevelStr GetCurrentWindowLevel(misUID imageUID);
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() const;
	std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> GetAllPackageViewers() const;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllLandMarkViewers() const override;

	// Return viewers that are not image viewer!
	std::vector<std::shared_ptr<IVolume3DRenderer>> Get3DViewers() override;
	std::vector<std::shared_ptr<IVolumeSlicer>> Get2DViewers();

	void Reset(void) override;
	void ClearViewers() override;
	void ReleaseResource();

	void Remove3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep);
	void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom) override;
	void ShowPackageImages(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom) override;
	int ShowVolumes(VolumeDataDependencyListTypes NewVolumeDataDependencies) override;


	void SetTransformMatrix(vtkMatrix4x4* transform);
	void SetImageColor(std::vector<misUID> UIDs, misColorStruct imageColor);
	misColorStruct GetImageColor(std::vector<misUID> UIDs);

	void SetOrientation(IMAGEORIENTATION newOrientation) override;
	void ChangeViewerToMultipleImages() override;
	void ShowPlan(std::shared_ptr<parcast::IPackagePlanRel> rel) override;

	void UpdateRepresentationTransforms(std::shared_ptr<ISimpleDataPackage> package) override;
	void SetDentalSurgeryType(DentalSurgeryType surgeryType);
	virtual void Freeze();
	virtual void Unfreeze();
	virtual void SetObliqueFlag(bool isObiquw) final;
	virtual void SetCroppingDirection(misCroppingDirectionInVR croppingDirection, const double* center, bool isOblique);
	virtual void Reset2DZoom();
	virtual void ClipVolumeWithObliquePlane(const double* planeNormal, const double* center);
	void SetAnnotationDetailToViewer();
	void ClearAnnotationDetailFromViewer() override;
	void UpdateViewerROI(misROI roi);
	void ResetROI(misROI roi);
	void ResetROI();
	void UpdateViewerWithImage(std::shared_ptr<IImage> image);
	void SetPanoramicTransformConvertor(std::shared_ptr<IPanoramicTransformConverter> panoramicTransformConvertor);
	void UpdateSliderInGUI() override;
	virtual void ClippingOff();
	std::shared_ptr<IVolumeRenderer> GetViewerByType(misViewerTypeDirection type) const override;
	void SetExternalEventViewer(std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> val) override;
	void SetRoiWidgetActivation(const double* roi, bool activation) override;
	void UpdatePanoramicCurve() override;
	std::shared_ptr<IPanoramicCoordinatesConverter> GetPanoramicCoordinateConverter() const override;
	unsigned long AddObserver(const itk::EventObject& event, itk::Command* command) override;
	bool HasObserver(const itk::EventObject& event) const override;
	void InvokeEvent(const itk::EventObject& event) override;
	std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp> GetRenderingToolExtension() const override;
	void RefreshCurrentPackage() override;
	void SetPlanCentricViewAngle(double angle) override;
	void Add2DViewer(std::shared_ptr<IPackage2DDataRenderingAdapter> viewer, std::shared_ptr<Iwindows> window) override;
	void Add3DViewer(std::shared_ptr<IPackage3DDataRenderingAdapter> viewer, std::shared_ptr<Iwindows> window) override;
	void SetDefaultVisibilityMap(std::vector<std::map<misPlaneEnum, bool>> map) override;
	void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) override;
	void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) override;
	void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) override;
	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) override;
	virtual std::vector<std::shared_ptr<Iwindows>> GetAllWindow() override;
	void WarnFlyZone(const std::vector<std::vector<PropertiesOfPixelInImageStr>>& FlyZoneStatus) override;
	void ShowPackage(std::shared_ptr<ISimpleDataPackage>, const misVisualizationSetting&, const misSegmentationSetting&,
		double minOpacity, bool resetZoom, misCursorType pWidgetType,
		std::map<misPlaneEnum, bool> pPlaneVisible) override;
	void ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	void UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	void UpdateRepresentationTransforms(std::shared_ptr<IVolumeRenderer> viewer,
		std::shared_ptr<ISimpleDataPackage> newPackage) override;
	void UpdateRepresentationTransforms() override;
	void ReleaseImageResources() override;
	void SetWidgetType(misCursorType pWidgetType) override;
	std::shared_ptr<IVolumeRenderer> GetViewer() override;
	void SetSceneReferenceCoordinateSystem(const std::string& coordSysUid, std::shared_ptr<ISimpleDataPackage> package)
		override;
	void SetDentalSpecialViewsEnable(std::shared_ptr<IVolumeRenderer> viewer, bool enabled) override;
	void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter,
		std::shared_ptr<IVolumeRenderer> viewer) override;
	int ShowSegmentedObjects(const misSegmentationSetting&, ImageContainedPolydataDependencyListTypes,
		double minOpacity) override;
	int ShowPlans(std::shared_ptr<IVolumeRenderer> viewer,
		std::shared_ptr<PlanDataListDependencyTypedef> rels) override;
	void UpdatePosition(parcast::Point<double, 3> position) override;
	void SetVisibilityOfSegmentedImage(misUID imageuid, bool val) override;
	void ChangeViewerToSameImages() override;

private:

	void ApplyShowAnnotationDetailToViewer(bool show);
	void InitializeGeneralTimers(void);
	void ChangeInteractionState(itk::Object* caller, const itk::EventObject& event);
	void DistributeEvent(itk::Object* caller, const itk::EventObject& pEvent);
	void HandleUpdatePositionEvent(const misUpdatePositionEvent* pEvent);
	void SetPanoCoordConverterToPackageViewers(std::shared_ptr<ISimpleDataPackage> pPackage);

	// Check which viewer invoked event -  
	bool FindDistributerViewer(itk::Object* caller, size_t& viewerIndex);
	void Add2DInternalObservers();
	void ShowFPS(bool showFPS);
	void SetErasedObjDisplayStatus(bool DisplayStatus);
	void SetErasedObjColor(misColorStruct ColorStr);
	virtual void DisableWidget();
	void UpdateImageAnnotation(misVolumeSlicer* imageViewer);
	void ShowPackgeIn2DAdapter(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom);
	void ShowPackageIn3dAdapter(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom);
		void AddObservers(std::shared_ptr<IVolumeRenderer> viewer);
	void UpdatePlaneVisibilities(std::vector<std::map<misPlaneEnum, bool>> pPlaneVisible) override;

	misApplicationSetting* m_AppSetting;
	std::shared_ptr<ISubsequenceLayout> m_Model;
	std::shared_ptr<IGroupViewerSetting> m_GroupViewSetting;
	misN4VStateVarible m_StateVars;
	std::vector<std::shared_ptr<Iwindows>> m_Windows;
	std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> m_2DViewers;
	std::vector<std::shared_ptr<IPackage3DDataRenderingAdapter>> m_3DViewers;
	std::map<std::vector<misUID>, misColorStruct> m_ImagesColor;
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CSCorrelationManager;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicTransformConvertor;
	std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> m_ExternalEventViewer;
	std::shared_ptr<IPanoramicCoordinatesConverter> m_PanoramicCoordinateConverter;
	std::weak_ptr<IObliqueChanged> m_ObliqueChangedObserver;
	std::weak_ptr<IPlanSelectedInViewer> m_PlanSelectedInViewerObserver;
	bool m_RereadPanoramicCurve = true;
	std::shared_ptr<Injector> m_Injector;
	itk::Object::Pointer m_DummyObject = itk::Object::New();
	std::weak_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::vector<std::map<misPlaneEnum, bool>> m_DefaultVisibilityPlan;
	std::vector<vtkSmartPointer<vtkTextActor>> flyZoneStatusText;
	std::shared_ptr<IUpdateViewPortToStandard> m_UpdateViewPortsToStandard;
	std::shared_ptr<IUpdateViewPortToOblique> m_UpdateViewPortsToOblique;
};
