#include "stdafx.h"
#include "misDataSetManager.h"

#include "Adapters/PackageRepo.h"
#include "ExtLibWrappers/PackagePlanRelFactory.h"
#include "ExtLibWrappers/PlanFactory.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRepository.h"
#include "IImage.h"
#include "ISimpleDataPackage.h"
#include "misCompositeDataPackage.h"
#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misDataSetManagerUtilities.h"
#include "misImageContained.h"
#include "misImageDataProperties.h"
#include "misImageUtilities.h"
#include "misLogger.h"
#include "misMathUtils.h"
#include "misPlanData.h"
#include "misSolutionProperty.h"
#include "misStringTools.h"
#include "misTransform.h"
#include "IVolumeData.h"
#include "PackagePlanRelRepo.h"
#include "PlanRepo.h"
#include "PlanTransformCalculator.h"
#include "TransformFactory.h"
#include "misVolumeDataDependensies.h"
#include "misViewableElement.h"
#include "PackageListViewingType.h"
#include "misConfirmedImageCounter.h"
#include "cln_MemoryTestApplication.h"

using namespace std;
using itk::LoggerBase;

// Remove the redundancy in plans: all plans are currently stored both in the respective package and dataset manager.
misDatasetManager::misDatasetManager()
	: m_Logger(misLogger::GetInstance())
{
	m_CSCorrelationManager = std::make_shared<misCoordinateSystemCorrelationTreeManager>();
	m_PackageRepo = std::make_shared<parcast::PackageRepo>();
	m_PlanRepo = std::make_shared<parcast::PlanRepo>();
	m_PackagePlanRelRepo = std::make_shared<parcast::PackagePlanRelRepo>();
	m_PlanTransformCalculator = std::make_shared<parcast::PlanTransformCalculator>();
	m_TransformFactory = std::make_shared<parcast::TransformFactory>();
	m_PackagePlanRelFactory = std::make_shared<parcast::PackagePlanRelFactory>(m_PackageRepo, m_PlanRepo);
	m_PlanFactory = std::make_shared<parcast::PlanFactory>(
		m_PackagePlanRelRepo, m_CSCorrelationManager, m_PlanTransformCalculator, m_TransformFactory, m_PlanRepo);
	m_PackageSData = &m_PackageRepo->GetPackageDataSForDatasetManager();
	m_SolotionProperty = std::make_shared<misSolutionProperty>(m_PackageRepo);
	m_PlanRepo->SetPackagePlanRelRepo(m_PackagePlanRelRepo);
	m_PlanRepo->SetPlanFactory(m_PlanFactory);
	m_PackagePlanRelRepo->SetRelFactory(m_PackagePlanRelFactory);
}

misDatasetManager* misDatasetManager::GetInstance(bool destroySingletonInstance)
{
	static misDatasetManager* singleton;
	if (destroySingletonInstance && singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
	else if (!singleton)
	{
		singleton = new misDatasetManager();
	}
	return singleton;
}

void misDatasetManager::DeletePackageRelatedToImage(misUID imageUID)
{
	auto packages = GetPackageDataByImageUID(imageUID);
	if (packages.size() > 0)
	{
		for each (auto package in packages)
		{
			RemovePackage(package->GetObjectUID());
		}
	}
	m_CSRepository->RemoveCoordinateSystem(GetCoordinateSystem(imageUID));
	Update();
}

std::shared_ptr<parcast::ITreatmentSolution> misDatasetManager::GetCurrentSolution() const
{
	return GetSolutionProperty();
}

std::shared_ptr<parcast::IPackageRepo> misDatasetManager::GetPackageRepo() const
{
	return m_PackageRepo;
}

std::shared_ptr<parcast::IPlanRepo> misDatasetManager::GetPlanRepo() const
{
	return m_PlanRepo;
}

std::shared_ptr<parcast::IPackagePlanRelRepo> misDatasetManager::GetPackagePlanRelRepo() const
{
	return m_PackagePlanRelRepo;
}

std::weak_ptr<parcast::IPlanTransformCalculator> misDatasetManager::GetPlanTransformCalculator() const
{
	return m_PlanTransformCalculator;
}

void misDatasetManager::ResetSolution()
{
	m_CSRepository->Clear();
	m_PackageSData->clear();
	m_VolumeDatas.clear();
	auto mem1 = cln_MemoryTestApplication::GetInstance()->GetProccessMemoryConsumeInMegaByteByRam();
	auto res = 0;
	for(auto image : m_Images)

	{
		auto ext1 = image->GetRawImageData()->GetExtent();
		auto sum1 =  ((ext1[1]+1 - ext1[0]) * (ext1[3]+1 - ext1[2]) * (ext1[5]+1 - ext1[4]) * 2);
		res += sum1;
	}
	for (auto contained : m_ImageContainedPolyDatas)

	{
		auto image = GetImage(contained->GetParentImageUID());
		auto ext1 = image->GetRawImageData()->GetExtent();
		auto sum1 = ((ext1[1]+1 - ext1[0]) * (ext1[3]+1 - ext1[2]) * (ext1[5]+1 - ext1[4]) * 2);
		res += sum1;
	}
 
 
	m_Images.clear();
	m_ImageContainedPolyDatas.clear();
	m_SolotionProperty->Reset();
	std::list<ICoordinateSystemCorrelationManager<std::string>::DirectCorrelation> emptyCorrelationsList;
	if (m_CSCorrelationManager)
	{
		m_CSCorrelationManager->SetDirectCorrelationsList(emptyCorrelationsList);
	}
	m_PlanRepo->Clear();
	auto mem2 = cln_MemoryTestApplication::GetInstance()->GetProccessMemoryConsumeInMegaByteByRam();
	std::cout << " Size : " << mem1 - mem2;
}


misResultCode::ResultIds misDatasetManager::Update(void)
{
	UpdatePackegeSDataPointer();
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
	return misResultCode::NoError;
}

misResultCode::ResultIds misDatasetManager::UpdatePackegeSDataPointer(void)
{
	for (auto packageItr = m_PackageSData->begin(); packageItr != m_PackageSData->end(); packageItr++)
	{
		(*packageItr)->UpdateImageSDataPointer(m_Images);
		(*packageItr)->UpdateImageContainedPolyDataSDataPointer(m_ImageContainedPolyDatas);
		(*packageItr)->UpdateVolumeSDataPointer(&m_VolumeDatas);
	}
	return misResultCode::NoError;
}


void misDatasetManager::AddImage(std::shared_ptr<IImage> image)
{
	if (!image)
	{
		return;
	}

 
	auto problemList = misImageUtilities::CheckImageValidity(image);
	if (InAcceptedImageProblem == problemList[0])
	{
		return;
	}

	bool duplicatedImage = misDataSetManagerUtilities::FindDuplicatedImageInDataset(m_Images, image->GetPrimeryUID());
	if (duplicatedImage)
	{
		return;
	}

	// to equal the patient properties of solution with that be attach for the image 
	image->SetResterictedPatientProperties(m_SolotionProperty->GetPatientProperties());
	auto primaryUID = image->GetPrimeryUID();
	m_Images.push_back(image);
	AddNewPackageData(image);
	
}

std::shared_ptr<IImage> misDatasetManager::GetImage(misUID imageUID)
{
	auto foundImageItr = find_if(m_Images.cbegin(), m_Images.cend(), [&imageUID](std::shared_ptr<IImage> image) -> bool
	{
		return image->GetUID() == imageUID;
	});
	if (foundImageItr != m_Images.cend())
	{
		return *foundImageItr;
	}
	return 0;
}

misResultCode::ResultIds misDatasetManager::DeleteImage(misUID imageUID)
{
	auto imageItr = std::find_if(m_Images.begin(), m_Images.end(), [&](std::shared_ptr<IImage> image)->bool
	{
		return imageUID == image->GetUID();
	});

	if (imageItr != m_Images.end())
	{
		m_Images.erase(imageItr);
		DeletePackageRelatedToImage(imageUID);
		DeleteContaindPolydata(imageUID);
		UpdatePackegeSDataPointer();
		auto pPackage = GetHybridPackageDataByImageUID(imageUID);
		if (pPackage)
		{
			auto packageUID = pPackage->GetObjectUID();
			return DeleteHybridPackageData(packageUID);
		}
	}
	return misResultCode::NoError;
}

std::shared_ptr<IImageContained> misDatasetManager::GetImageContaindPolydataByParentUID(misUID imageUID)
{
	for (auto imageItr = m_ImageContainedPolyDatas.begin(); imageItr != m_ImageContainedPolyDatas.end(); imageItr++)
	{
		if ((*imageItr)->GetParentImageUID() == imageUID)
		{
			return *imageItr;
		}
	}
	return 0;
}

std::shared_ptr<IVolumeData> misDatasetManager::GetVolumeDataByParentUID(misUID imageUID)
{
	for (auto volumeItr = m_VolumeDatas.begin(); volumeItr != m_VolumeDatas.end(); volumeItr++)
	{
		if ((*volumeItr)->GetParentImageUID() == imageUID)
		{
			return *volumeItr;
		}
	}
	return 0;
}

std::shared_ptr<IImageContained> misDatasetManager::GetImageContaindPolydata(misUID imageUID)
{
	for (auto imageItr = m_ImageContainedPolyDatas.begin(); imageItr != m_ImageContainedPolyDatas.end(); imageItr++)
	{
		if (0 == imageUID.compare((*imageItr)->GetUID()))
		{
			return *imageItr;
		}
	}
	return nullptr;
}

ImageContainedPolyDataListTypedef misDatasetManager::GetContaindPolydataS()
{
	return m_ImageContainedPolyDatas;
}

misResultCode::ResultIds misDatasetManager::DeleteContaindPolydata(misUID imageUID)
{
	auto foundImg = find_if(m_ImageContainedPolyDatas.begin(), m_ImageContainedPolyDatas.end(),
		[imageUID](auto img) -> bool
	{
		return img->GetUID() == imageUID;
	});
	if (foundImg == m_ImageContainedPolyDatas.end())
	{
		return misResultCode::ErUnableToFindInList;
	}
	m_ImageContainedPolyDatas.erase(foundImg);
	return misResultCode::NoError;
}

misResultCode::ResultIds misDatasetManager::AddVolumeData(const misVolumeDataDependensies& pVolumeDependency)
{
	if (!pVolumeDependency.GetVolume())
	{
		return misResultCode::ErEmptyPointer;
	}

	auto volumeDataUID = pVolumeDependency.GetVolume()->GetUID();
	if (volumeDataUID == "")
	{
		return misResultCode::ErEmptyObjectUID;
	}

	auto parentImageUID = pVolumeDependency.GetVolume()->GetParentImageUID();
	if (parentImageUID == "")
	{
		return misResultCode::ErEmptyParrentImageUID;
	}

	bool res = misDataSetManagerUtilities::FindDuplicatedVolumeDataInDataset(&m_VolumeDatas, volumeDataUID, parentImageUID);
	if (res)
	{
		return misResultCode::ErDuplicatedObjectNotPermitable;
	}

	m_VolumeDatas.push_back(pVolumeDependency.GetVolume());
	misResultCode::ResultIds result;
	auto currentHybidPackage = GetHybridPackageDataByImageUID(parentImageUID);
	if (currentHybidPackage)
	{
		misObjectVisibilityMap visibleParts = pVolumeDependency.GetAllObjectVisibility();
		result = currentHybidPackage->AddNextVolumedata(volumeDataUID, parentImageUID, visibleParts);
		UpdatePackegeSDataPointer();
	}
	return result;
}

std::shared_ptr<IVolumeData> misDatasetManager::GetVolumeData(misUID volumeDateUID)
{
	for (auto volumeDataIterator = m_VolumeDatas.begin(); volumeDataIterator != m_VolumeDatas.end(); volumeDataIterator++)
	{
		if (0 == volumeDateUID.compare((*volumeDataIterator)->GetUID()))
		{
			return *volumeDataIterator;
		}
	}
	return nullptr;
}

std::shared_ptr<IImageContained> misDatasetManager::GetImageContained(misUID imageContainedUid)
{
	for (auto imageContainedDataIterator = m_ImageContainedPolyDatas.begin(); imageContainedDataIterator != m_ImageContainedPolyDatas.end(); imageContainedDataIterator++)
	{
		if (0 == imageContainedUid.compare((*imageContainedDataIterator)->GetUID()))
		{
			return *imageContainedDataIterator;
		}
	}
	return 0;
}

VolumeDataListTypedef* misDatasetManager::GetMisVolumeDataS()
{
	return &m_VolumeDatas;
}

std::shared_ptr<ISimpleDataPackage> misDatasetManager::GetPackageData(misUID packageUID)
{
	for (auto packageItr = m_PackageSData->cbegin(); packageItr != m_PackageSData->cend(); packageItr++)
	{
		if ((*packageItr)->GetObjectUID() == packageUID)
		{
			return *packageItr;
		}
	}
	return 0;
}

std::shared_ptr<ISimpleDataPackage> misDatasetManager::GetHybridPackageDataByImageUID(misUID imageUID)
{
	auto packageItr = find_if(m_PackageSData->cbegin(), m_PackageSData->cend(), [&](std::shared_ptr<ISimpleDataPackage>  package)->bool
	{
		if (package->GetMainImageUID() == imageUID)
		{
			return true;
		}
		return false;
	});
	if (packageItr != m_PackageSData->end())
	{
		return *packageItr;
	}
	return NULL;
}


PackagesListTypedef misDatasetManager::GetPackageDataByImageUID(misUID imageUID)
{
	PackagesListTypedef packageList;
	for (auto packageItr = m_PackageSData->cbegin(); packageItr != m_PackageSData->cend(); packageItr++)
	{
		auto imageDependencies = (*packageItr)->GetImageDataDependencies();
		auto foundUid = std::find_if(
			imageDependencies.cbegin(), imageDependencies.cend(), [imageUID](const auto  &imgDep) -> bool
		{
			return (imgDep->GetObjectUID() == imageUID);
		});
		if (foundUid != imageDependencies.cend())
		{
			packageList.push_back(*packageItr);
		}
	}
	return packageList;
}

misResultCode::ResultIds misDatasetManager::DeleteCompositePackageData(misUID packageUID)
{
	auto newEndItr = std::remove_if(m_PackageSData->begin(), m_PackageSData->end(), [&](std::shared_ptr<ISimpleDataPackage> pkg) -> bool
	{
		if (pkg->GetObjectUID() == packageUID && pkg->GetObjectType() == misCompositePackageType)
		{
			return true;
		}
		return false;
	});
	if (newEndItr == m_PackageSData->end())
	{
		return misResultCode::ErUnableToFindInList;
	}

	m_PackageSData->resize(newEndItr - m_PackageSData->begin());
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
	return misResultCode::NoError;
}

misResultCode::ResultIds misDatasetManager::DeleteHybridPackageData(misUID packageUID)
{
	auto newEndItr = std::remove_if(m_PackageSData->begin(), m_PackageSData->end(), [&](std::shared_ptr<ISimpleDataPackage> pkg) -> bool
	{
		if (pkg->GetObjectUID() == packageUID && pkg->GetObjectType() == misHybridPackageType)
		{
			return true;
		}
		return false;
	});
	if (newEndItr == m_PackageSData->end())
	{
		return misResultCode::ErUnableToFindInList;
	}

	m_PackageSData->resize(newEndItr - m_PackageSData->begin());
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
	return misResultCode::NoError;
}

void misDatasetManager::RemovePackage(const misUID& packageUID)
{
	auto newEndItr = std::remove_if(m_PackageSData->begin(), m_PackageSData->end(), [&](std::shared_ptr<ISimpleDataPackage> pkg) -> bool
	{
		if (pkg->GetObjectUID() == packageUID)
		{
			return true;
		}
		return false;
	});
	m_PackageSData->resize(newEndItr - m_PackageSData->begin());
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
}

int misDatasetManager::GetMinimumAccptedImageNumber() const
{
	return m_MinimumAccptedImageNumber;
}

void misDatasetManager::SetMinimumAccptedImageNumber(int val)
{
	m_MinimumAccptedImageNumber = val;
}

ImageListTypedef misDatasetManager::GetImages() const
{
	return m_Images;
}

PackagesListTypedef misDatasetManager::GetPackageDataS() const
{
	return *m_PackageSData;
}

IDatasetManager::WeakPackagesListTypedef misDatasetManager::GetWeakPackageDataS() const
{
	auto packages = *m_PackageSData;
	WeakPackagesListTypedef weakListPackges;
	for (auto package : packages)
	{
		weakListPackges.push_back(package);
	}
	return weakListPackges;
}

int misDatasetManager::GetNumberOfImages(ImageListViewingType viewingType)
{
	if (Complete == viewingType)
	{
		return m_Images.size();
	}

	if (OnlyConfirmedDirection == viewingType)
	{
		int numberOfImages = 0;
		for (auto imageItr = m_Images.begin(); imageItr != m_Images.end(); imageItr++)
		{
			if ((*imageItr)->GetConfirmedDirection())
			{
				numberOfImages++;
			}
		}
		return numberOfImages;
	}
	return 0;
}

ImageViewingListTypedef misDatasetManager::GetImageSViewingList(ImageListViewingType viewingType)
{
	ImageViewingListTypedef viewingList;
	for (auto imageIterator = m_Images.begin(); imageIterator != m_Images.end(); imageIterator++)
	{
		auto imageViewingStr = (*imageIterator)->GetViewingStrct();
		imageViewingStr.makeCompleteName = m_ImageViewingNameCompletenessStatus;
		imageViewingStr.Update();

		if (Complete == viewingType || imageViewingStr.directionSataus)
		{
			viewingList.push_back(imageViewingStr);
		}
	}
	return viewingList;
}

void misDatasetManager::AddNewPackageData(std::shared_ptr<IImage> image)
{
	if (!image)
	{
		return;
	}
	PackagesListTypedef newPackages;
	bool foundImageDep = false;
	std::for_each(m_PackageSData->begin(), m_PackageSData->end(), [&](std::shared_ptr<ISimpleDataPackage> package)
	{
		auto imageDependancy = package->GetImageDataDependencies();
		for (auto imgeDep : imageDependancy)
		{
			if (imgeDep->GetObjectUID() == image->GetUID())
			{
				package->SetImageToRelatedImageDataDependancy(image);
				foundImageDep = true;
			}
		}
	});
	if (!foundImageDep)
	{
		std::shared_ptr<ISimpleDataPackage> newPackage = std::make_shared<misSimpleDataPackage>(GetPackagePlanRelRepo());
		newPackage->SetName(image->GetName());
		newPackage->SetImageToRelatedImageDataDependancy(image);
		newPackages.push_back(newPackage);
		m_PackageSData->insert(m_PackageSData->end(), newPackages.begin(), newPackages.end());
	}
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
}

void misDatasetManager::DeletePlanning(misUID planDataUID)
{
	m_PlanRepo->Delete(planDataUID);
}

PackageViewingListTypedef misDatasetManager::GetPackageViewingList(PackageListViewingType viewingType) const
{
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
	auto imageConfirmedCounter = std::make_shared<misConfirmedImageCounter>();
	misViewableElement elemnts(*m_PackageSData, m_CSCorrelationManager, imageConfirmedCounter);
	return elemnts.GetPackageViewingList(viewingType);
}

misResultCode::ResultIds misDatasetManager::AddNewPackageData(std::shared_ptr<ISimpleDataPackage> pMisPackageData)
{
	if (!pMisPackageData)
	{
		return misResultCode::ErEmptyPointer;
	}

	bool isDupe = misDataSetManagerUtilities::FindDuplicatedPackageInDatasetManager(
		*m_PackageSData, pMisPackageData->GetObjectUID());

	if (isDupe)
	{
		return misResultCode::ErDuplicatedObjectNotPermitable;
	}

	m_PackageSData->push_back(pMisPackageData);
	Update();
	return misResultCode::NoError;
}

string misDatasetManager::GetAutomaticObjectName(MisObjectType objectType)
{
	string objectName;
	int objectNumber = 0;

	if (misImageType == objectType)
	{
		objectName = "ImageSerie :";
		objectNumber = m_Images.size();
	}
	else if ((misPolyDataType == objectType) || (misVolumeDataType == objectType))
	{
		objectName = "3D Model :";
		objectNumber = m_VolumeDatas.size();
	}

	// Remove the redundancy in plans: all plans are currently stored both in the respective package and dataset manager.
	else if ((misPlanDataType == objectType) /*|| ( misBiopsyPlanDataType == objectType)*/)
	{
		objectName = "3D Model :";
		objectNumber = m_PlanRepo->GetAllPlans().size();
	}
	else if ((misHybridPackageType == objectType) || (misCompositePackageType == objectType))
	{
		objectName = "Packege :";
		objectNumber = m_PackageSData->size();
	}
	else
	{
		objectName = "New Object:";
	}

	objectNumber = objectNumber + 1;
	auto nomStr = misStringTools::IntToString(objectNumber);
	objectName.append(nomStr);
	return objectName;
}

misResultCode::ResultIds misDatasetManager::SetPatientProperties(misPatientProperties patientProperties)
{
	if (m_SolotionProperty)
	{
		m_SolotionProperty->SetPatientProperties(patientProperties);
	}
	for (auto imageIterator = m_Images.begin(); imageIterator != m_Images.end(); imageIterator++)
	{
		(*imageIterator)->SetResterictedPatientProperties(patientProperties);
	}
	return misResultCode::NoError;
};

misResultCode::ResultIds misDatasetManager::AddNewPackageDataByCorrelatedImages(misCorrelatedImagesStr correlatedImages)
{
	if ((correlatedImages.FirstImageUID == "") || (correlatedImages.secondImageUID == ""))
	{
		return misResultCode::ErEmptyObjectUID;
	}

	auto image1 = GetImage(correlatedImages.FirstImageUID);
	if (0 == image1)
	{
		return misResultCode::ErEmptyPointer;
	}

	auto image2 = GetImage(correlatedImages.secondImageUID);
	if (0 == image2)
	{
		return misResultCode::ErEmptyPointer;
	}

	bool newPackage = true;
	for (auto listIterator = m_PackageSData->begin(); listIterator != m_PackageSData->end(); listIterator++)
	{
		// find Composite Package
		if (misCompositePackageType == ((*listIterator))->GetObjectType())
		{
			auto comPacakgePointer = std::dynamic_pointer_cast<misCompositeDataPackage> (*listIterator);
			if (comPacakgePointer) // It is for double check
			{
				auto res = comPacakgePointer->ComparePackage(correlatedImages);
				if (misResultCode::ErDuplicatedpackage == res)
				{
					newPackage = false;
					break;
				}
			}
		}
	}
	if (newPackage)
	{
		auto correlatedPackage = std::make_shared<misCompositeDataPackage>();
		correlatedPackage->SetCSCorrelationManager(m_CSCorrelationManager);
		correlatedPackage->SetImageToRelatedImageDataDependancy(image1);
		correlatedPackage->SetImageToRelatedImageDataDependancy(image2);
		AddNewPackageData(correlatedPackage);
	}
	return misResultCode::NoError;
}


misResultCode::ResultIds misDatasetManager::MergePackageDataS(std::shared_ptr<ISimpleDataPackage> existedPack)
{
	if (!existedPack)
	{
		return misResultCode::ErEmptyPointer;
	}

	auto packageUID = existedPack->GetObjectUID();
	DeleteCompositePackageData(packageUID);
	m_PackageSData->push_back(existedPack);
	Update();
	misDataSetManagerUtilities::UpdatePackageNames(*m_PackageSData);
	return misResultCode::NoError;
}

misResultCode::ResultIds misDatasetManager::AddVolume(std::shared_ptr<IVolumeData> pVolumeData)
{
	if (!pVolumeData)
	{
		return misResultCode::ErEmptyPointer;
	}

	auto foundVolumeItr = find_if(m_VolumeDatas.cbegin(), m_VolumeDatas.cend(), [&pVolumeData](std::shared_ptr<IVolumeData> volume) -> bool
	{
		return volume->GetUID() == pVolumeData->GetUID();
	});
	if (foundVolumeItr == m_VolumeDatas.cend())
	{
		m_VolumeDatas.push_back(pVolumeData);
		return misResultCode::NoError;
	}
	return misResultCode::ErDuplicatedObjectNotPermitable;
}

misResultCode::ResultIds misDatasetManager::AddImageContained(std::shared_ptr<misImageContained> pImageContainedPoly)
{
	if (!pImageContainedPoly)
	{
		return misResultCode::ErEmptyPointer;
	}

	auto foundContainedObject = find_if(m_ImageContainedPolyDatas.cbegin(), m_ImageContainedPolyDatas.cend(),
		[pImageContainedPoly](auto containedObject) -> bool
	{
		return pImageContainedPoly->GetUID() == containedObject->GetUID();
	});
	if (foundContainedObject == m_ImageContainedPolyDatas.cend())
	{
		m_ImageContainedPolyDatas.push_back(pImageContainedPoly);
	}

	return misResultCode::NoError;
}

PlanDataListTypedef misDatasetManager::GetPlanDataList()
{
	return m_PlanRepo->GetAllPlans();
}

std::shared_ptr<misSolutionProperty> misDatasetManager::GetSolutionProperty() const
{
	return m_SolotionProperty;
}

std::string misDatasetManager::GetPatientUID() const
{
	return m_SolotionProperty->GetPatientProperties().PatientUID;
}

std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > misDatasetManager::GetCSCorrelationManager() const
{
	return m_CSCorrelationManager;
}

std::shared_ptr<ICoordinateSystem> misDatasetManager::GetCoordinateSystem(misUID id)
{
	return m_CSRepository->GetCoordinateSystem(id);
}

void misDatasetManager::AddCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem)
{
	m_CSRepository->AddCoordinateSystem(coordinateSystem);
	auto image = std::dynamic_pointer_cast<IImage>(coordinateSystem);
	if (image)
	{
		AddImage(image);
	}

	auto segement = std::dynamic_pointer_cast<misImageContained>(coordinateSystem);
	if (segement)
	{
		AddImageContained(segement);
	}


	auto volume = std::dynamic_pointer_cast<IVolumeData>(coordinateSystem);
	if (volume)
	{
		AddVolume(volume);
	}
}

void misDatasetManager::RemoveCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinateSystem)
{
	m_CSRepository->RemoveCoordinateSystem(coordinateSystem);
}

void misDatasetManager::SetCSRepository(std::shared_ptr<ICoordinateSystemRepository> val)
{
	m_CSRepository = val;
}

misUID misDatasetManager::GetRegisteredPackageUID()
{
	auto regImageUID = m_SolotionProperty->GetRegisteredImageUID();
	for (auto packageItr = m_PackageSData->begin(); packageItr != m_PackageSData->end(); packageItr++)
	{
		auto imageDepList = (*packageItr)->GetImageDataDependencies();
		for (auto imageItr : imageDepList)
		{
			if (regImageUID == (*imageItr).GetObjectUID())
			{
				return (*packageItr)->GetObjectUID();
			}
		}
	}
	return "";
}
