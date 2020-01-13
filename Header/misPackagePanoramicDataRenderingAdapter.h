#pragma once
#include "misPackageDataRenderingAdapter.h"
#include "IPackage2DDataRenderingAdapter.h"
#include "IViewerFactory.h"

class misPackagePanoramicDataRenderingAdapter : public IPackage2DDataRenderingAdapter,
                                                public misPackageDataRenderingAdapter, public IOblqueView
{
public:

	using misPackageDataRenderingAdapter::misPackageDataRenderingAdapter;
	misPackagePanoramicDataRenderingAdapter(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<Iwindows> pWindow, int index, misSurgeryDirectionViewerType currentTypeDir, double offset,
		std::shared_ptr<misPanoramicViewer> viewer, std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater);

	misWindowLevelStr GetCurrentWindowLevel(std::string imageUID) override;
	void ApplyWindowlevel(std::string imageUID, misWindowLevelStr winLevStr) override;
	void SetOpacityValueToTexture(misUID imageUID, float val) override;
	void SetVisibilityValueToTexture(misUID imageUID, bool val) override;
	void SetOrientation(IMAGEORIENTATION newOrientation);
	int ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting,
		ImageContainedPolydataDependencyListTypes newImageContainedPolydataDependencies, double minOpacity) override;
	void ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	int ShowVolumes(VolumeDataDependencyListTypes NewVolumeDataDependencies) override;
	void ShowPlan(std::shared_ptr< parcast::IPackagePlanRel> rel) override;
	virtual void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, const misVisualizationSetting& visualSetting,
		const misSegmentationSetting& segmentationSetting, double minOpacity, bool resetZoom, misCursorType pWidgetType,
		std::map<misPlaneEnum, bool> pPlaneVisible) override;
	virtual void Reset() override;
	virtual void ReleaseImageResources() override;
	virtual void SetWidgetType(misCursorType pWidgetType) override;

	void SetColorValueToTexture(misUID imageUID, misDoubleColorStruct Color) override;
	void UpdatePosition(parcast::Point<double, 3> position) override;
	void SetObliqueFlag(bool isOblique) override;
	void UpdateImageAnnotation(void) override;
	void ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/,
		LANDMARKLABLETYPE lableType) override;
	void ImageLandmarkCaptureDisable() override;
	void ImageLandmarkUpdateEnable(misLandmarkType, int) override;
	void ImageLandmarkUpdateDisable() override;
	void AddInternalObservers(itk::Command* ContrastObserver, itk::Command* backToMapObserver,
		itk::Command* stateObsrever) override;
	void SetRealTimeMode(bool val) override;
	void ResetMeasurment() override;
	std::shared_ptr<IVolumeRenderer> GetViewer() override;
	virtual void UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	virtual int ShowPlans(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef>) override;
	void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) override;
	void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) override;
	void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) override;
	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) override;
	void UpdateSliderInGUI() override;
	bool ShowImages(std::shared_ptr<ISimpleDataPackage> newPackage, const misVisualizationSetting& visualSetting,
		double minOpacity, bool resetZoom, misCursorType pWidgetType, std::shared_ptr<IImage>& mainImage) override;


private:

	void SetSpline(const std::vector<itk::Point<double, 3>>& splinePoints);

public:
	std::shared_ptr<IVolumeSlicer> GetSlicer() override;
	void SetVisibilityOfSegmentedImage(misUID imageuid, bool val) override;
private:
	misApplicationSetting*  m_AppSettingInstance;
	int m_NumberOfViewableObject;
	std::shared_ptr<misPanoramicViewer> m_viewer;

};

