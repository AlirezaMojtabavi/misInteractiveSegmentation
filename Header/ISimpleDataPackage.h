#pragma once

#include "misPackageViewingItemsStrct.h"
#include "misResultCode.h"
#include "misStrctDataSets.h"
#include "misMacros.h"
#include "misMacros.h"
#include "mis3DModelViewingProperties.h"
#include "misSTRCT.h"
#include "ICompeleteImageContainedPolydataDependensiesStrct.h"
#include "IPackagePlanRelRepo.h"
#include "IImageContained.h"
#include "IVolumeData.h"
#include "IVolumeDataDependency.h"

template <class T>
class ICoordinateSystemCorrelationManager;
class IImage;
class misCompeleteImageContainedPolydataDependensiesStrct;
class ICompeleteImageDependencies;
class misLandMarkBase;

struct misCompeletePolyDataDependensiesStrct;


namespace parcast
{
	class IPlan;
}

typedef std::map<misUID, mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityMap;
typedef std::vector<std::weak_ptr<parcast::IPlan>> PlanDataListTypedef;
typedef std::vector<misLandmarkPointStrct> misLandmarkListTypdef;;

// The ISimpleDataPackage encapsulate a collection of visualizable elements including: images, plans, segmented objects, 
// volume(color maps)and their visual properties (opacity, color, ..)
class ISimpleDataPackage
{
public:
	virtual ~ISimpleDataPackage() = default;

	typedef std::vector<std::shared_ptr<IImage>> ImageListTypedef;
	typedef std::vector<std::shared_ptr<ICompeleteImageDependencies>> ImageDependencyListTypes;
	typedef std::vector<std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct>>
		ImageContainedPolydataDependencyListTypes;
	typedef std::vector<misCompeletePolyDataDependensiesStrct> PolyDataDependencyListTypes;
	typedef std::vector<std::shared_ptr<parcast::IPackagePlanRel>> PlanDataListDependencyTypedef;
	typedef std::vector<std::shared_ptr<IVolumeDataDependency>> VolumeDataDependencyListTypes;
	typedef std::vector<std::shared_ptr<IImageContained>> ImageContainedPolyDataListTypedef;
	typedef std::vector<std::shared_ptr<IVolumeData>> VolumeDataListTypedef;

	virtual void SetObjectUID(const misUID& dataUID) = 0;
	virtual misUID GetObjectUID() const = 0;
	virtual void SetName(std::string name) = 0;
	virtual std::string GetName() const = 0;
	virtual MisObjectType GetObjectType() const = 0;
	virtual misShortImageViewingStrct GetImageDataProperties(misUID objectUID) = 0;
	virtual misShort3DModelViewingStrct Get3DModelDataProperties(misUID objectContainerUID, misUID objectUID) = 0;
	virtual misShortPlanningViewingStruct GetPlanDataProperties(misUID objectUID) = 0;
	virtual void SetObjectVisibility(misUID objectContainerUID, misUID objectUID, bool isVisible,
		misPresentationDimension presentationDim) = 0;
	virtual void SetObjectOpacity(misUID objectContainerUID, misUID objectUID, double opacity) = 0;
	virtual misResultCode::ResultIds SetObjectColor(misUID objectUID, misColorStruct color) = 0;
	virtual misResultCode::ResultIds SetImagedataOpacity(misUID objectUID, double visible) = 0;
	virtual void SetImagedataVisibility(misUID objectUID, bool visible) = 0;

	virtual int GetNumberOfImages() const = 0;
	virtual int GetNumberOf3DModels() = 0;
	virtual size_t GetNumberOfPlanes() const = 0;
	virtual std::shared_ptr<IImage> GetMainImage() const = 0;
	// Return all images in image dependencies of package
	virtual std::vector<std::shared_ptr<IImage>> GetImages() const = 0;
	virtual misUID GetMainImageUID() const = 0;
	virtual std::shared_ptr<ICompeleteImageDependencies> GetMainImageProperites()  const= 0;
	virtual misResultCode::ResultIds SetImageContainedPolyData(misUID mianImageUID) = 0;
	virtual misResultCode::ResultIds AddNextImageContainedPolydata(misUID pImageData, misUID parentImageUID) = 0;
	virtual misResultCode::ResultIds AddNextPolydata(misUID pPolydata, misUID parrentImageUID) = 0;
	virtual misResultCode::ResultIds AddNextVolumedata(misUID pVolumedata, misUID parrentImageUID,
		misObjectVisibilityMap visibleParts) = 0;
	virtual misResultCode::ResultIds AddNextSegmentedData(misUID objectContainer, misUID parentImageUID,
		misObjectVisibilityMap) = 0;
	virtual misResultCode::ResultIds AddNextImageContainedPolydata(
		std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> imageDataDependency) = 0;
	virtual misResultCode::ResultIds AddNextPolydata(misCompeletePolyDataDependensiesStrct polydataDependency) = 0;
	virtual misResultCode::ResultIds AddNextVolumedata(
		std::shared_ptr<IVolumeDataDependency> volumedataDependency) = 0;
	virtual misResultCode::ResultIds UpdateVolumedata(misUID pVolumedata, misObjectVisibilityMap visibleParts) = 0;

	virtual ImageDependencyListTypes GetImageDataDependencies() const = 0;
	virtual ImageContainedPolydataDependencyListTypes GetImageContainedPolydataDependencies() const = 0;
	virtual PolyDataDependencyListTypes GetPolyDataDependencies() const = 0;
	virtual VolumeDataDependencyListTypes GetVolumeDataDependencies() const = 0;
	virtual std::shared_ptr<PlanDataListDependencyTypedef> GetPlanDataDependencies() = 0;

	virtual misLandMarkBase* GetLandMarkPointer() = 0;
	virtual misLandmarkListTypdef GetLandMarkPoints() = 0;

	virtual bool SetLandMarkPoints(misLandmarkListTypdef landMarkPoints) = 0;
	virtual void DeleteAllLandmarks() = 0;

	virtual bool Delete3DModel(misUID objectContainerUID, misUID ObjectUID) = 0;
	virtual misResultCode::ResultIds DeleteVolumedata(misUID volumeDataUID) = 0;
	virtual void DeleteAllVolumedatas() = 0;
	// Important Note : all Update pointers must call after the UpdateImageSDataPointer calling
	virtual misResultCode::ResultIds UpdateImageSDataPointer(ImageListTypedef imagePointerList) = 0;
	virtual misResultCode::ResultIds UpdateImageContainedPolyDataSDataPointer(
		ImageContainedPolyDataListTypedef imagePointerList) = 0;
	virtual misResultCode::ResultIds UpdateVolumeSDataPointer(VolumeDataListTypedef* volumeDataPointerList) = 0;
	virtual misResultCode::ResultIds DeleteSegmentedObject(misUID segmentedObjUID, misUID objectContainerUID) = 0;
	virtual misResultCode::ResultIds DeleteRenderingObject(misUID renderedUID, misUID volumedataUID) = 0;
	virtual MisObjectType FindObjectType(misUID objectUID) = 0;
	virtual misResultCode::ResultIds ResetPackage() = 0;
	virtual misResultCode::ResultIds InvisibleAllPlanDatas() = 0;
	virtual misResultCode::ResultIds SetMarginAlaram(misUID containerUID, misUID SegmentedObjectUID, bool val) = 0;
	virtual misResultCode::ResultIds ShowMarginRegion(misUID containerUID, misUID SegmentedObjectUID, bool val) = 0;
	virtual misResultCode::ResultIds DeletePlanData(misUID planDataUID) = 0;
	virtual std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> GetCSCorrelationManager() const = 0;
	virtual void SetCSCorrelationManager(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> val) = 0;
	virtual void SetImageToRelatedImageDataDependancy(std::shared_ptr<IImage> image) = 0;
	// used by databased
	virtual misResultCode::ResultIds SetImageDataDependencies(const ImageDependencyListTypes& imageDataSDependencies) = 0;
	virtual misResultCode::ResultIds SetImageContainedPolyDataDependencies(
		ImageContainedPolydataDependencyListTypes imageDataSDependencies) = 0;
	virtual void SetVolumeDataDependencies(VolumeDataDependencyListTypes volumeDataSDependencies) = 0;
	virtual misResultCode::ResultIds SetPolyDataDependencies(PolyDataDependencyListTypes* polydataSDependencies) = 0;
	// Set/Get parametric spline used in panoramic view of the Dental mode
	typedef std::vector<itk::Point<double, 3>> PointListType;
	virtual PointListType GetParametricSpline() const = 0;
	virtual void SetParametricSpline(const PointListType& val) = 0;

	// Set/Get approximate length of the parametric spline used in panoramic view of  the Dental mode
	virtual void CreateVolumeFromImage(std::shared_ptr<IImage> image, double threshold, misApplicationType appType) = 0;

	virtual std::shared_ptr<PlanDataListTypedef> ExtractPlansListFromPackage() = 0;
	virtual std::string GetFlyzoneStatus(const double* position) = 0;
};
