#pragma once

#include "IRootEntity.h"
#include "misCorrelationStr.h"
#include "misResultCode.h"
#include "misPackageViewingItemsStrct.h"
#include "misStrctPatientData.h"
#include "PackageListViewingType.h"
#include "IImageContained.h"

class ICoordinateSystem;
template <class T> class ICoordinateSystemCorrelationManager;
class ICoordinateSystemRepository;
class IImage;
class ISimpleDataPackage;
class ICompeleteImageDependencies;
class misSolutionProperty;
class IVolumeData;
class misVolumeDataDependensies;

namespace parcast
{
	class IPlan;
	class IPackageRepo;
	class IPlanRepo;
	class IPackagePlanRelRepo;
	class IPlanTransformCalculator;
}

class IDatasetManager : public parcast::IRootEntity
{
public:
	typedef std::vector< std::shared_ptr<IImage> > ImageListTypedef;
	typedef std::vector<std::shared_ptr<ICompeleteImageDependencies>> ImageDependencyListTypes;
	typedef std::vector< std::shared_ptr<IImageContained> > ImageContainedPolyDataListTypedef;
	typedef std::vector< std::shared_ptr<ISimpleDataPackage> > PackagesListTypedef;
	typedef std::vector< std::weak_ptr<ISimpleDataPackage> > WeakPackagesListTypedef;
	typedef std::vector< std::weak_ptr<parcast::IPlan> > PlanDataListTypedef;
	typedef std::vector< std::shared_ptr<IVolumeData> > VolumeDataListTypedef;

	virtual misResultCode::ResultIds SetPatientProperties(misPatientProperties patientProperties) = 0;
	virtual std::string GetAutomaticObjectName(MisObjectType objectType) = 0;
	virtual ImageViewingListTypedef GetImageSViewingList(ImageListViewingType viewingType) = 0;
	virtual PackageViewingListTypedef GetPackageViewingList(PackageListViewingType viewingType) const = 0;
	virtual int GetNumberOfImages(ImageListViewingType viewingType) = 0;
	virtual misResultCode::ResultIds MergePackageDataS(std::shared_ptr<ISimpleDataPackage> existedPack) = 0;
	virtual misResultCode::ResultIds Update (void) = 0;
	virtual misResultCode::ResultIds UpdatePackegeSDataPointer(void) = 0;
	virtual void ResetSolution(void) = 0;
	virtual std::shared_ptr<IImage> GetImage (misUID imageUID) = 0;
	virtual ImageListTypedef GetImages (void) const = 0;
	virtual std::shared_ptr<IImageContained> GetImageContaindPolydataByParentUID (misUID imageUID) = 0;
	virtual std::shared_ptr<IImageContained> GetImageContaindPolydata(misUID imageUID) = 0;
	virtual ImageContainedPolyDataListTypedef GetContaindPolydataS (void) = 0;
	virtual misResultCode::ResultIds AddVolumeData (const misVolumeDataDependensies& pVolumeDependency) = 0;
	virtual std::shared_ptr<IVolumeData> GetVolumeData (misUID volumeDateUID) = 0;
	virtual std::shared_ptr<IVolumeData> GetVolumeDataByParentUID (misUID imageUID) = 0;
	virtual VolumeDataListTypedef* GetMisVolumeDataS (void) = 0;
	virtual misResultCode::ResultIds AddNewPackageData(std::shared_ptr<ISimpleDataPackage> pMisPackageData) = 0;
	virtual PackagesListTypedef GetPackageDataS (void) const = 0;
	virtual WeakPackagesListTypedef GetWeakPackageDataS(void) const = 0;
	virtual std::shared_ptr<ISimpleDataPackage> GetPackageData (misUID packageUID) = 0;
	virtual misResultCode::ResultIds DeleteCompositePackageData(misUID packageUID) = 0;
	virtual std::shared_ptr<ISimpleDataPackage> GetHybridPackageDataByImageUID (misUID imageUID) = 0;
	virtual PackagesListTypedef GetPackageDataByImageUID (misUID imageUID) = 0;
	virtual PlanDataListTypedef	GetPlanDataList() = 0;
	virtual misResultCode::ResultIds AddNewPackageDataByCorrelatedImages( misCorrelatedImagesStr correlatedImages ) = 0;
	virtual std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCSCorrelationManager() const = 0;
	virtual std::shared_ptr<misSolutionProperty> GetSolutionProperty() const = 0;
	virtual std::shared_ptr<ICoordinateSystem> GetCoordinateSystem(misUID id) = 0;
	virtual std::shared_ptr<ICoordinateSystemRepository> GetCSRepository() const = 0;
	virtual void SetCSRepository(std::shared_ptr<ICoordinateSystemRepository> val) = 0;
	virtual void AddCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem) = 0;
	virtual void RemoveCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem) =  0;
	virtual void DeletePlanning(misUID planDataUID) = 0;
	virtual misResultCode::ResultIds DeleteImage(misUID imageUID) = 0;
	virtual misResultCode::ResultIds DeleteContaindPolydata (misUID imageUID) = 0;
	virtual misUID GetRegisteredPackageUID() = 0;
	// Remove package from dataset manager
	virtual void RemovePackage(const misUID& packageUID) = 0;
	virtual int GetMinimumAccptedImageNumber() const = 0;
	virtual void SetMinimumAccptedImageNumber(int val) = 0;
	virtual void DeletePackageRelatedToImage(misUID imageUID) = 0;
	virtual std::string GetPatientUID() const = 0;
	virtual std::shared_ptr<parcast::IPackageRepo> GetPackageRepo() const = 0;
	virtual std::shared_ptr<parcast::IPlanRepo> GetPlanRepo() const = 0;
	virtual std::shared_ptr<parcast::IPackagePlanRelRepo> GetPackagePlanRelRepo() const = 0;
	virtual std::weak_ptr<parcast::IPlanTransformCalculator> GetPlanTransformCalculator() const = 0;

	virtual ~IDatasetManager() = default;
};