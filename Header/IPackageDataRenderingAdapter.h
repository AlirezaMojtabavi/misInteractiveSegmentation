#pragma once
#pragma warning( disable : 4250 )

#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"
#include "misPlaneContrast.h"
#include "IVolumeDataDependency.h"
#include "ICompeleteImageContainedPolydataDependensiesStrct.h"
#include "misCompeletePlanDataDependensiesStrct.h"
#include "misStrctColorData.h"
#include "IVolumeRenderer.h"

class IVolume3DRenderer;
template <class T> class ICoordinateSystemCorrelationManager;
class IPanoramicCoordinatesConverter;
class ISimpleDataPackage;
class Iwindows;
class misCompeletePlanDataDependensiesStrct;
class IVolumeDataDependency;

struct misSegmentationSetting;
struct misVisualizationSetting;


enum misCursorType;
typedef std::vector<std::shared_ptr<IVolumeDataDependency>> VolumeDataDependencyListTypes;
typedef std::vector<std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct>>
ImageContainedPolydataDependencyListTypes;

class IPackageDataRenderingAdapter 
{
public:
	virtual void SetVolumeViewingType(misVolumeViewingTypes volumeViewingType) = 0;
	virtual void ShowPackage(std::shared_ptr<ISimpleDataPackage>, const misVisualizationSetting&,
		const misSegmentationSetting&, double minOpacity, bool resetZoom, misCursorType pWidgetType,
		std::map<misPlaneEnum, bool> pPlaneVisible) = 0;
	virtual void ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp) = 0;
	virtual void UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp) = 0;
	virtual int ShowVolumes(VolumeDataDependencyListTypes NewVolumeDataDependencies) = 0;
	// Reset an remove all representation from viewer
	virtual  void Reset() = 0;
	virtual void UpdateRepresentationTransforms(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<ISimpleDataPackage> newPackage) = 0;
	// Release rendering resource include texure and voume representation and plans and landmarks
	// Update representation transform(gpu image representation , volume , ) from correlation tree
	virtual void UpdateRepresentationTransforms() = 0;

	virtual void ReleaseImageResources() = 0;
	virtual void SetWidgetType(misCursorType pWidgetType) = 0;
	virtual std::shared_ptr<IVolumeRenderer> GetViewer() = 0;
	virtual void SetSceneReferenceCoordinateSystem(const std::string& coordSysUid, 
		std::shared_ptr<ISimpleDataPackage> package) = 0;
	virtual void SetDentalSpecialViewsEnable(std::shared_ptr<IVolumeRenderer> viewer, bool enabled) = 0;
	virtual void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter>
		coordinateConverter, std::shared_ptr<IVolumeRenderer> viewer) = 0;
	virtual int ShowSegmentedObjects(const misSegmentationSetting&, ImageContainedPolydataDependencyListTypes, double minOpacity) = 0;
	virtual void ShowPlan(std::shared_ptr< parcast::IPackagePlanRel> rel) = 0;
	virtual int ShowPlans(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef> rels) = 0;
	virtual void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) = 0;
	virtual void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) = 0;
	virtual void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) = 0;
	virtual	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) = 0;
	virtual void UpdatePosition(parcast::Point<double, 3> position) = 0;
	virtual void SetVisibilityOfSegmentedImage(misUID imageuid, bool val) = 0;

	virtual ~IPackageDataRenderingAdapter() = default;
};
