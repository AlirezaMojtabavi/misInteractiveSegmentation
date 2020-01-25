#pragma once

#include "I3DImageRenderer.h"
#include "IVolume3DRenderer.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "IPackage3DDataRenderingAdapter.h"
#include "IPackageTransformUpdater.h"
#include "IPackageDataAdapter.h"
#include "ISimpleDataPackage.h"
#include "ITFIAddressMapper.h"
#include "mis3DViewer.h"
#include "misApplicationSetting.h"
#include "misObject.h"
#include "misPackageDataRenderingAdapter.h"
#include "misPlanarRepresentation.h"
#include "misSurgeryDirectionViewerType.h"
#include "misViewerTypeDirection.h"
#include "misVolumeRenderingStrategy.h"
#include "IVolumeRayCaster.h"
#include "IViewerFactory.h"
#include "mis3DImageRenderer.h"
#include "IDefaultVolumeRenderer.h"
#include "IOblqueView.h"
#include "ILandmarkViewer.h"

typedef std::vector<std::shared_ptr<IVolumeDataDependency>> VolumeDataDependencyListTypes;
 
	class   misPackage3DDataRenderingAdapter :public IPackage3DDataRenderingAdapter,public IOblqueView,
		public misPackageDataRenderingAdapter
	{
	public:

		misPackage3DDataRenderingAdapter(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
			std::shared_ptr<Iwindows> pWindow,
			int index,
			misSurgeryDirectionViewerType currentTypeDir,
			std::shared_ptr<IVolume3DRenderer>  viewer,
			std::shared_ptr<mis3DImageRenderer> imageRenderer,
			std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater,
			std::shared_ptr<IVolumeViewerInitilizer> volumeinitializer);
		misPackage3DDataRenderingAdapter() = delete;
		void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, const misVisualizationSetting& visualSetting, 
			const misSegmentationSetting& segmentationSetting, double minOpacity, bool resetZoom, misCursorType pWidgetType,
		                 std::map<misPlaneEnum, bool> pPlaneVisible) override;
		void Reset() override;
		void ReleaseImageResources() override;
		void SetWidgetType(misCursorType pWidgetType) override;
		void ModifyVolume() override;
		void ShowPlan(std::shared_ptr< parcast::IPackagePlanRel>) override;
		void ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
		int ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting, 
			ImageContainedPolydataDependencyListTypes newImageContainedPolydataDependencies, double minOpacity) override;
		int ShowVolumes(VolumeDataDependencyListTypes newVolumeDataDependencies) override;
		virtual std::shared_ptr<IVolume3DRenderer> GetVolumeViewer() override;
		virtual void UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp) override;
		std::shared_ptr<IVolumeRenderer> GetViewer() override;
 		void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) override;
		void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) override;
		void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) override;
		void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) override;
		void UpdatePosition(parcast::Point<double, 3> position) override;
 		void SetVisibilityOfSegmentedImage(misUID imageuid, bool val) override;
		void SetObliqueFlag(bool isOblique) override;

	private:

		int ShowSegmentedObjectsIn3Dviewers(std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct>
			PolyContained);
		bool NeedToResetVolumes(int NewVolumeDataSize, int OldVolumeDataSize, VolumeDataDependencyListTypes
			&NewVolumeDataDependencies);
		int CreatePlansIn3Dviewers(std::shared_ptr< parcast::IPackagePlanRel> rel);
		std::shared_ptr<I3DImageRenderer> m_ImageRenderer;
		std::shared_ptr<IVolume3DRenderer> m_viewer;
		std::unique_ptr<IDefaultVolumeRenderer> m_DefaultVolumeRenderer;
		std::shared_ptr<IVolumeViewerInitilizer> m_VolumeViewerInitializer;
		misSegmentationSetting m_SegmentationSetting;
		misVisualizationSetting m_VisualizationSetting;
		std::map<misPlaneEnum, bool> m_PlaneVisibility;
		double m_MinOpacity = 0.1;
	};
