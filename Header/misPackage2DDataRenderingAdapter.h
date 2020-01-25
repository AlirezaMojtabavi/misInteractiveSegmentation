#pragma once

#include "misPackageDataRenderingAdapter.h"
#include "IPackage2DDataRenderingAdapter.h"
#include "IUpdatePlaneVisibilitiy.h"

class IRepresentationFactory;
class IVolumeSlicer;
class I2DImageRenderingAdapter;
typedef std::vector<std::shared_ptr<IVolumeDataDependency>> VolumeDataDependencyListTypes;

class misPackage2DDataRenderingAdapter : public IPackage2DDataRenderingAdapter, public misPackageDataRenderingAdapter, public IOblqueView
{
public:

	using misPackageDataRenderingAdapter::misPackageDataRenderingAdapter;
	misPackage2DDataRenderingAdapter(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		misSurgeryDirectionViewerType currentTypeDir, double offset,
		std::shared_ptr<IVolumeSlicer> viewer2D,
		std::shared_ptr<IRepresentationFactory> representationFactory, 
		std::unique_ptr<I2DImageRenderingAdapter> imageRenderer,
		std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater);
	~misPackage2DDataRenderingAdapter();
	misWindowLevelStr GetCurrentWindowLevel(std::string imageUID) override;
	void ApplyWindowlevel(std::string imageUID, misWindowLevelStr winLevStr) override;
	void SetOpacityValueToTexture(misUID imageUID, float val) override;
	void SetVisibilityValueToTexture(misUID imageUID, bool val) override;
	void SetOrientation(IMAGEORIENTATION newOrientation);
	int ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting,
		ImageContainedPolydataDependencyListTypes newImageContainedPolydataDependencies, double minOpacity) override;
	void ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	int ShowVolumes(VolumeDataDependencyListTypes newVolumeDataDependencies) override;
	void ShowPlan(std::shared_ptr< parcast::IPackagePlanRel> rel) override;
	bool ShowImages(std::shared_ptr<ISimpleDataPackage> newPackage, const misVisualizationSetting& visualSetting,
		double minOpacity, bool resetZoom, misCursorType pWidgetType, std::shared_ptr<IImage>& mainImage) override;
	void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, const misVisualizationSetting& visualSetting,
		const misSegmentationSetting& segmentationSetting, double minOpacity, bool resetZoom, misCursorType pWidgetType, std::map<misPlaneEnum, bool> pPlaneVisible) override;
	void Reset() override;
	void ReleaseImageResources() override;
	void SetWidgetType(misCursorType pWidgetType) override;
	void SetColorValueToTexture(misUID imageUID, misDoubleColorStruct Color) override;
	void UpdatePosition(parcast::Point<double, 3> position) override;
	void SetObliqueFlag(bool isOblique) override;
	void UpdateImageAnnotation() override;
	void AddInternalObservers(itk::Command* ContrastObserver, itk::Command* backToMapObserver,
		itk::Command* stateObsrever) override;
	void SetRealTimeMode(bool val) override;
	void ResetMeasurment() override;
	std::shared_ptr<IVolumeRenderer> GetViewer() override;
	void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) override;
	void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) override;
	void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) override;
	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) override;
	void UpdateSliderInGUI() override;
	std::shared_ptr<IVolumeSlicer> GetSlicer() override;
	void SetVisibilityOfSegmentedImage(misUID imageuid, bool val) override;


private:

	void UpdateSliders();
	void UpdateImagePlaneDimension(ImageDependencyListTypes &images);
	int CreateScrewPlansIn2Dviewers(std::shared_ptr< parcast::IPackagePlanRel> rel);
	void RemoveImageLyer(std::shared_ptr<I2DRepresetation> Gpu2DRep);
	int ShowSegmentedObjectsIn2Dviewers(
		const std::shared_ptr<const ICompeleteImageContainedPolydataDependensiesStrct>& PolyContained,
		double minOpacity);
	misPlaneEnum GetCorrespondingPlaneIndex(misUID ParentImageUID);
	void SetSegmentedTextureUIDVisibility(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf);
	void SetVolumeTextureUIDVisibility(misPlaneEnum CorrespondingPlaneEnum, std::shared_ptr<TransFuncIntensity> val);
	void UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
	std::unique_ptr<I2DImageRenderingAdapter> m_ImageRenderer;
	misApplicationSetting*  m_AppSettingInstance;
	int m_NumberOfViewableObject;
	std::shared_ptr<IVolumeSlicer> m_Slicer;
};

