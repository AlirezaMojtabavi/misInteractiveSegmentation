#pragma once

#include "IDatasetManager.h"
#include "misSimpleDataPackage.h"
#include "misStrctDataSets.h"
#include "ITreatmentSolution.h"

MOCK_BASE_CLASS(MockDatasetManager, IDatasetManager)
{
	MOCK_NON_CONST_METHOD(SetPatientProperties, 1, misResultCode::ResultIds (misPatientProperties ));
	MOCK_NON_CONST_METHOD(GetAutomaticObjectName,1, std::string (MisObjectType ));
	MOCK_NON_CONST_METHOD(GetImageSViewingList,1, ImageViewingListTypedef (ImageListViewingType ));
	MOCK_CONST_METHOD(GetPackageViewingList, 1, PackageViewingListTypedef(PackageListViewingType ));
	MOCK_NON_CONST_METHOD(GetNumberOfImages, 1, int (ImageListViewingType ));
	MOCK_NON_CONST_METHOD(MergePackageDataS, 1, misResultCode::ResultIds (std::shared_ptr<ISimpleDataPackage> ));
	MOCK_NON_CONST_METHOD(Update , 0, misResultCode::ResultIds (void));
	MOCK_NON_CONST_METHOD(UpdatePackegeSDataPointer,  0, misResultCode::ResultIds (void));
	MOCK_NON_CONST_METHOD(ResetSolution, 0, void(void));
	MOCK_NON_CONST_METHOD(GetImage , 1, std::shared_ptr<IImage>(misUID ));
	MOCK_CONST_METHOD(GetImages , 0, ImageListTypedef(void));
	MOCK_NON_CONST_METHOD(GetImageContaindPolydataByParentUID , 1, std::shared_ptr<IImageContained> (misUID ));
	MOCK_NON_CONST_METHOD(GetImageContaindPolydata, 1, std::shared_ptr<IImageContained> (misUID ));
	MOCK_NON_CONST_METHOD(GetContaindPolydataS ,0, ImageContainedPolyDataListTypedef (void));
	MOCK_NON_CONST_METHOD(AddVolumeData, 1, misResultCode::ResultIds  (const misVolumeDataDependensies&));
	MOCK_NON_CONST_METHOD(GetVolumeData , 1, std::shared_ptr<IVolumeData>(misUID ));
	MOCK_NON_CONST_METHOD(GetVolumeDataByParentUID , 1, std::shared_ptr<IVolumeData> (misUID ));
	MOCK_NON_CONST_METHOD(GetMisVolumeDataS , 0, VolumeDataListTypedef*(void));
	MOCK_NON_CONST_METHOD(AddNewPackageData, 1, misResultCode::ResultIds (std::shared_ptr<ISimpleDataPackage>));
	MOCK_CONST_METHOD(GetPackageDataS , 0, PackagesListTypedef (void));
	MOCK_CONST_METHOD (GetWeakPackageDataS, 0, WeakPackagesListTypedef(void));
	MOCK_NON_CONST_METHOD(GetPackageData, 1, std::shared_ptr<ISimpleDataPackage> (misUID));
	MOCK_NON_CONST_METHOD(DeleteCompositePackageData, 1, misResultCode::ResultIds (misUID));
	MOCK_NON_CONST_METHOD(GetHybridPackageDataByImageUID , 1, std::shared_ptr<ISimpleDataPackage>(misUID));
	MOCK_NON_CONST_METHOD(GetPackageDataByImageUID, 1, PackagesListTypedef(misUID));
	MOCK_NON_CONST_METHOD(GetPlanDataList, 0, PlanDataListTypedef());
	MOCK_NON_CONST_METHOD(AddNewPackageDataByCorrelatedImages, 1, misResultCode::ResultIds(misCorrelatedImagesStr));
	MOCK_NON_CONST_METHOD(GetImageSCorrelationViewingList, 1, ImageCorrelationViewingListTypedef (ImageListViewingType));
	MOCK_CONST_METHOD(GetCSCorrelationManager, 0, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >());
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void (std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >));
	MOCK_CONST_METHOD(GetSolutionProperty, 0, std::shared_ptr<misSolutionProperty>());
	MOCK_NON_CONST_METHOD(GetCoordinateSystem, 1, std::shared_ptr<ICoordinateSystem> (misUID));
	MOCK_CONST_METHOD(GetCSRepository, 0, std::shared_ptr<ICoordinateSystemRepository>());
	MOCK_NON_CONST_METHOD(SetCSRepository, 1, void (std::shared_ptr<ICoordinateSystemRepository>));
	MOCK_NON_CONST_METHOD(AddCoordinateSystem, 1, void (std::shared_ptr<ICoordinateSystem>));
	MOCK_NON_CONST_METHOD(RemoveCoordinateSystem, 1,  void (std::shared_ptr<ICoordinateSystem> ) );

	MOCK_NON_CONST_METHOD(DeletePlanning, 1, void (misUID));
	MOCK_NON_CONST_METHOD(DeleteImage, 1, misResultCode::ResultIds (misUID));
	MOCK_NON_CONST_METHOD(DeleteContaindPolydata, 1, misResultCode::ResultIds  (misUID));
	MOCK_NON_CONST_METHOD(GetRegisteredPackageUID, 0, misUID());
	
	// Remove package from dataset manager
	MOCK_NON_CONST_METHOD(RemovePackage, 1, void(const misUID&));
	MOCK_CONST_METHOD(GetMinimumAccptedImageNumber, 0, int());
	MOCK_NON_CONST_METHOD(SetMinimumAccptedImageNumber, 1, void (int));
	MOCK_CONST_METHOD(GetImageViewingNameCompletenessStatus, 0, bool());
	MOCK_NON_CONST_METHOD(SetImageViewingNameCompletenessStatus, 1, void(bool));
	MOCK_NON_CONST_METHOD(DeletePackageRelatedToImage,1,void(misUID imageUID));
	MOCK_CONST_METHOD(GetPatientUID, 0 , std::string () );
	MOCK_CONST_METHOD(GetCurrentSolution, 0, std::shared_ptr<parcast::ITreatmentSolution>());
	MOCK_CONST_METHOD(GetPackageRepo, 0, std::shared_ptr<parcast::IPackageRepo> ());
	MOCK_CONST_METHOD(GetPlanRepo, 0, std::shared_ptr<parcast::IPlanRepo>());
	MOCK_CONST_METHOD(GetPackagePlanRelRepo, 0, std::shared_ptr<parcast::IPackagePlanRelRepo>());
	MOCK_CONST_METHOD(GetPlanTransformCalculator, 0, std::weak_ptr<parcast::IPlanTransformCalculator>());
};