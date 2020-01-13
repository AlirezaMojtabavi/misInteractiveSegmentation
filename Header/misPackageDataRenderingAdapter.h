#pragma once

 #include "IVolume3DRenderer.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "IPackageDataRenderingAdapter.h"
#include "IPackageTransformUpdater.h"
#include "ISimpleDataPackage.h"
#include "misApplicationSetting.h"
#include "misPlanarRepresentation.h"
#include "misSurgeryDirectionViewerType.h"
#include "misViewerTypeDirection.h"


class misPackageDataRenderingAdapter : public virtual IPackageDataRenderingAdapter
{
public:
	misPackageDataRenderingAdapter(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater, 
		misSurgeryDirectionViewerType currentTypeDir);
	~misPackageDataRenderingAdapter() = default;

	void SetVolumeViewingType(misVolumeViewingTypes volumeViewingType) override;
	void UpdateRepresentationTransforms(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<ISimpleDataPackage> newPackage) override;
	void UpdateRepresentationTransforms() override;
	void SetSceneReferenceCoordinateSystem(const std::string& coordSysUid, std::shared_ptr<ISimpleDataPackage> package) override;
	void SetDentalSpecialViewsEnable(std::shared_ptr<IVolumeRenderer> viewer, bool enabled) override;
	int ShowPlans(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef> rels) override;

protected:
	double GetSliceViewerZoomFactor(const misVisualizationSetting& visualSetting , 
		misViewerTypeDirection orientation, misImageDataModality modality);

	void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter,
	                                     std::shared_ptr<IVolumeRenderer> viewer) override;
	misVolumeViewingTypes m_VolumeViewingType;
	std::weak_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<IPackageTransformUpdater> m_PackageTransformUpdater;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	ImageContainedPolydataDependencyListTypes m_CurrentImageContainedPolydataDependencies;
	VolumeDataDependencyListTypes m_CurrentVolumeDataDependencies;
	misSurgeryDirectionViewerType	m_CurrentTypeDir;
	misCursorType m_WidgetType;
	misUID m_SceneReferenceUID;
	bool m_DentalSpecialViewEnable = false;
private:
	std::shared_ptr<TransFuncIntensity> GenerateTransferFunctionForPolyContainedData(
		std::shared_ptr<misImageContained> imageContainedPolyData, misUID ImageContainedUID = "");



};

