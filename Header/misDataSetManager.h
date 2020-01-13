#pragma once

#include "IDatasetManager.h"
#include "PackageListViewingType.h"

namespace parcast
{
	class PackageRepo;
	class PackagePlanRelFactory;
	class PlanFactory;
	class IPlanTransformCalculator;
	class IPackagePlanRelRepo;
	class PackagePlanRelRepo;
	class IPlanRepo;
	class PlanRepo;
	class TransformFactory;
}

template < typename CST >
class ICoordinateSystemCorrelationManager;
class ISimpleDataPackage;
class misImageContained;
class misPlanData;
class misSolutionProperty;
class misLogger;

class misDatasetManager : public IDatasetManager
{
public:
	friend class misCreateCompositeSubSeq;
	friend class misSolutionInformationDatabaseIO;
	friend class misSolutionInitializer;

	// Raise the destroySingletonInstance flag ONLY in test tear down procedures
	static misDatasetManager* GetInstance(bool destroySingletonInstance = false);

	misResultCode::ResultIds SetPatientProperties(misPatientProperties patientProperties);
	std::string GetAutomaticObjectName(MisObjectType objectType);
	ImageViewingListTypedef GetImageSViewingList(ImageListViewingType viewingType);
	PackageViewingListTypedef GetPackageViewingList(PackageListViewingType viewingType) const override ;
	int GetNumberOfImages(ImageListViewingType viewingType);
	misResultCode::ResultIds MergePackageDataS(std::shared_ptr<ISimpleDataPackage> existedPack);
	misResultCode::ResultIds Update();
	misResultCode::ResultIds UpdatePackegeSDataPointer();
	void ResetSolution();
	std::shared_ptr<IImage> GetImage(misUID imageUID);
	ImageListTypedef GetImages() const;
	std::shared_ptr<IImageContained> GetImageContaindPolydataByParentUID(misUID imageUID);
	std::shared_ptr<IImageContained> GetImageContaindPolydata(misUID imageUID);
	ImageContainedPolyDataListTypedef GetContaindPolydataS();
	misResultCode::ResultIds AddVolumeData(const misVolumeDataDependensies& pVolumeDependency);
	std::shared_ptr<IVolumeData> GetVolumeData(misUID volumeDateUID);
	std::shared_ptr<IImageContained> GetImageContained(misUID imageContainedUid);
	std::shared_ptr<IVolumeData> GetVolumeDataByParentUID(misUID imageUID);
	VolumeDataListTypedef* GetMisVolumeDataS();
	misResultCode::ResultIds AddNewPackageData(std::shared_ptr<ISimpleDataPackage> pMisPackageData);
	PackagesListTypedef GetPackageDataS() const ;
	WeakPackagesListTypedef GetWeakPackageDataS(void) const override;
	std::shared_ptr<ISimpleDataPackage> GetPackageData(misUID packageUID);
	misResultCode::ResultIds DeleteCompositePackageData(misUID packageUID);
	std::shared_ptr<ISimpleDataPackage> GetHybridPackageDataByImageUID(misUID imageUID);
	PackagesListTypedef GetPackageDataByImageUID(misUID imageUID);
	PlanDataListTypedef GetPlanDataList() override;
	misResultCode::ResultIds AddNewPackageDataByCorrelatedImages(misCorrelatedImagesStr correlatedImages);
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCSCorrelationManager() const;
	std::shared_ptr<misSolutionProperty> GetSolutionProperty() const override;
	std::string GetPatientUID() const override;
	std::shared_ptr<ICoordinateSystem> GetCoordinateSystem(misUID id) override;
	std::shared_ptr<ICoordinateSystemRepository> GetCSRepository() const { return m_CSRepository; }
	void SetCSRepository(std::shared_ptr<ICoordinateSystemRepository> val);
	//Add Coordinate System
	void AddCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem);
	void RemoveCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem) override;
	void DeletePlanning(misUID planDataUID);
	misResultCode::ResultIds DeleteImage(misUID imageUID);
	misResultCode::ResultIds DeleteContaindPolydata(misUID imageUID);
	misUID GetRegisteredPackageUID();
	// Remove package from dataset manager
	void RemovePackage(const misUID& packageUID);
	int GetMinimumAccptedImageNumber() const;
	void SetMinimumAccptedImageNumber(int val);
	void DeletePackageRelatedToImage(misUID imageUID) override;
	std::shared_ptr<parcast::ITreatmentSolution> GetCurrentSolution() const override;
	std::shared_ptr<parcast::IPackageRepo> GetPackageRepo() const override;
	std::shared_ptr<parcast::IPlanRepo> GetPlanRepo() const override;
	std::shared_ptr<parcast::IPackagePlanRelRepo> GetPackagePlanRelRepo() const override;
	std::weak_ptr<parcast::IPlanTransformCalculator> GetPlanTransformCalculator() const override;

private:
	misDatasetManager();
	~misDatasetManager() { }

	void AddImage(std::shared_ptr<IImage> image);
	misResultCode::ResultIds AddImageContained(std::shared_ptr<misImageContained> pImageContainedPoly);
	misResultCode::ResultIds AddVolume(std::shared_ptr<IVolumeData> pVolumeData);
	misResultCode::ResultIds DeleteHybridPackageData(misUID packageUID);

	void AddNewPackageData(std::shared_ptr<IImage> pMisImage);

	VolumeDataListTypedef m_VolumeDatas;
	ImageContainedPolyDataListTypedef m_ImageContainedPolyDatas;
	ImageListTypedef m_Images;
	//--------------------------------------------------------------------------------------------------------
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<parcast::PackageRepo> m_PackageRepo;
	std::shared_ptr<parcast::PlanRepo> m_PlanRepo;
	std::shared_ptr<parcast::PackagePlanRelRepo> m_PackagePlanRelRepo;
	std::shared_ptr<parcast::PackagePlanRelFactory> m_PackagePlanRelFactory;
	std::shared_ptr<parcast::IPlanTransformCalculator> m_PlanTransformCalculator;
	std::shared_ptr<parcast::TransformFactory> m_TransformFactory;
	std::shared_ptr<parcast::PlanFactory> m_PlanFactory;
	PackagesListTypedef* m_PackageSData;
	std::shared_ptr<misSolutionProperty> m_SolotionProperty;
	//--------------------------------------------------------------------------------------------------------
	std::shared_ptr<ICoordinateSystemRepository>  m_CSRepository;

	// set a flag to update package when related MRI image loaded
	bool m_fMRILoaded = false;

	misLogger*  m_Logger;
	int m_MinimumAccptedImageNumber;
	bool m_ImageViewingNameCompletenessStatus = true;
};
