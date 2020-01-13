#include "stdafx.h"

#include "ICompeleteImageDependencies.h"
#include "ModalityToViewingtypeConverter.h"
#include "misDataSetManager.h"
#include "misDataSetsUtility.h"
#include "misEnumUtilities.h"
#include "misImageContained.h"
#include "misLandMarkBase.h"
#include "misPlanData.h"
#include "misSimpleDataPackage.h"
#include "misStringTools.h"
#include "misVolumeDataDependensies.h"
#include "misCompeleteImageDependensies.h"
#include "misCompeleteImageContainedPolydataDependensiesStrct.h"
#include "PackagePlanRelRepo.h"
#include "misStrctVolumeData.h"
#include "misVolumeData.h"
#include "ImagePriorty.h"

using std::exception;
using std::for_each;

misSimpleDataPackage::misSimpleDataPackage(std::shared_ptr<parcast::IPackagePlanRelRepo> packagePlanRelRepo)
	:m_UIDSetOccurance(0),
	m_PackagePlanRelRepo(packagePlanRelRepo)
{
	m_ObjectType = misHybridPackageType;
	m_PolydataS = new PolyDataDependencyListTypes;
	m_DataObjectUID = misStringTools::GenerateNewUID();
	m_LandMark = new misLandMarkBase;
}

MisObjectType misSimpleDataPackage::GetObjectType() const
{
	return m_ObjectType;
}

misSimpleDataPackage::~misSimpleDataPackage()
{
	if (m_PolydataS)
	{
		delete m_PolydataS;
	}
	if (m_LandMark)
	{
		delete  m_LandMark;
	}
}

misResultCode::ResultIds misSimpleDataPackage::DeletePolydata(misUID polydataUID)
{
	misResultCode::ResultIds resultID;
	misUID containedUID;
	PolyDataDependencyListTypes::iterator listIterator;
	// Unable to find a special Image
	resultID = misResultCode::ErPolyDataNotExist;

	if (m_PolydataS->size() > 0)
	{
		for (listIterator = m_PolydataS->begin(); listIterator != m_PolydataS->end(); listIterator++)
		{
			containedUID = listIterator->objectUID;
			if (0 == containedUID.compare(polydataUID))
			{
				m_PolydataS->erase(listIterator);
				resultID = misResultCode::NoError;
				break;
			}
		}
	}
	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::DeleteImageContainedPolyData(misUID imageContainedPolyDataUID)
{
	auto resultID = misResultCode::ErUnableToDeleteFromList;
	if (m_PolydataS->empty())
	{
		return resultID;
	}
	auto deleted = std::remove_if(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&imageContainedPolyDataUID](const auto contained)
	{
		if (imageContainedPolyDataUID == contained->GetObjectUID())
		{
			return true;
		}
		return false;
	});

	if (deleted != m_ImageContaineds.end())
	{
		m_ImageContaineds.erase(deleted, m_ImageContaineds.end());
		resultID = misResultCode::NoError;
	}
	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::DeleteVolumedata(misUID volumeDataUID)
{
	misUID VolumeContainedUID;
	VolumeDataDependencyListTypes::iterator iter;
	auto resultID = misResultCode::ErUnableToDeleteFromList;
	auto removed = std::remove_if(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto volume)
	{
		VolumeContainedUID = volume->GetObjectUID();
		if (0 == volumeDataUID.compare(VolumeContainedUID))
		{
			return true;
		}
		return false;
	});
	if (removed != m_VolumeDataS.end())
	{
		resultID = misResultCode::NoError;
		m_VolumeDataS.erase(removed, m_VolumeDataS.end());
	}
	return resultID;
}

void misSimpleDataPackage::DeleteAllVolumedatas()
{
	m_VolumeDataS.clear();
}

misResultCode::ResultIds misSimpleDataPackage::DeletePlanData(misUID planDataUID)
{
	auto resultID = misResultCode::ErUnableToDeleteFromList;
	if (planDataUID == "")
	{
		return resultID;
	}

	m_PackagePlanRelRepo->Delete(m_DataObjectUID, planDataUID);
	return misResultCode::NoError;
}

void misSimpleDataPackage::AddNextImageData(std::shared_ptr<IImage> image)
{
	auto newImageDataDependency = std::make_shared<misCompeleteImageDependencies>();
	newImageDataDependency->SetObjectUID(image->GetUID());
	newImageDataDependency->SetName(image->GetName());
	newImageDataDependency->SetImage(image);
	m_ImageDataS.push_back(newImageDataDependency);
}

void misSimpleDataPackage::SetImageToRelatedImageDataDependancy(std::shared_ptr<IImage> image)
{
	auto foundedImageDependancy = std::find_if(m_ImageDataS.begin(), m_ImageDataS.end(),
		[&](auto imageDependancy)->bool
	{
		if (imageDependancy->GetObjectUID() == image->GetUID())
			return true;
		return false;
	});

	if (foundedImageDependancy == m_ImageDataS.end())
		AddNextImageData(image);
	else
		(*foundedImageDependancy)->SetImage(image);
}

misResultCode::ResultIds misSimpleDataPackage::AddNextImageContainedPolydata(misUID pImageDataUID, misUID parrentImageUID)
{
	std::shared_ptr<misCompeleteImageContainedPolydataDependensiesStrct>   newImageContainedDependency;
	newImageContainedDependency->GetObjectUID() = pImageDataUID;
	newImageContainedDependency->SetParentUID(parrentImageUID);

	misResultCode::ResultIds resultID = AddNextImageContainedPolydata(newImageContainedDependency);

	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::AddNextImageContainedPolydata(
	std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> imageDataDependency)
{
	if (!imageDataDependency)
		return  misResultCode::ErEmptyPointer;
	misResultCode::ResultIds  resultID = misResultCode::NoError;
	misUID  newObjectUID = imageDataDependency->GetObjectUID();
	//Check duplicate

	std::for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto completeImageContainedStrct)
	{
		if (newObjectUID == completeImageContainedStrct->GetObjectUID())
		{
			if (completeImageContainedStrct->GetImageContained())
			{
				resultID = misResultCode::ErDuplicatedObjectNotPermitable;
				return;
			}
			else
			{
				completeImageContainedStrct->SetImageContained(imageDataDependency->GetImageContained());
				resultID = misResultCode::ErDuplicatedObjectNotPermitable;
				return;
			}
		}
	});
	if (resultID == misResultCode::ErDuplicatedObjectNotPermitable)
	{
		return resultID;
	}
	try
	{
		m_ImageContaineds.push_back(imageDataDependency);
		resultID = misResultCode::NoError;

	}
	catch (exception* e)
	{
		resultID = misResultCode::ErUnableTOAddInList;
		cout << e->what();
	}

	if (1 == m_ImageContaineds.size())
		SetImageContainedPolyData(newObjectUID);
	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::AddNextPolydata(misUID   pPolydata, misUID parrentImageUID)
{
	misCompeletePolyDataDependensiesStrct   newPolydataDependency;
	newPolydataDependency.parentImageUID = parrentImageUID;
	newPolydataDependency.objectUID = pPolydata;
	misResultCode::ResultIds resultID = AddNextPolydata(newPolydataDependency);
	return resultID;
}

misResultCode::ResultIds   misSimpleDataPackage::AddNextPolydata(misCompeletePolyDataDependensiesStrct polydataDependency)
{
	misResultCode::ResultIds resultID;

	if (polydataDependency.objectUID == "")
	{
		return	 misResultCode::ErEmptyObjectUID;
	}

	misUID  newObjectUID = polydataDependency.objectUID;


	misUID newObjectParrentUID = polydataDependency.parentImageUID;

	resultID = AddingValidityStatus(newObjectParrentUID);
	if (misResultCode::NoError != resultID)
	{
		return resultID;
	}

	bool result;
	result = misDataSetsUtility::FindDuplicatedPolyDataInPackage(m_PolydataS, newObjectUID);

	if (true == result)
	{
		resultID = misResultCode::ErDuplicatedObjectNotPermitable;
		return	 resultID;
	}

	try
	{
		m_PolydataS->push_back(polydataDependency);
		resultID = misResultCode::NoError;

	}
	catch (exception* r)
	{
		resultID = misResultCode::ErUnableTOAddInList;
		cout << r->what();
	}

	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::AddNextVolumedata(
	std::shared_ptr<IVolumeDataDependency> volumedataDependency)
{
	auto resultID = AddingValidityStatus(volumedataDependency->GetParentImageUID());
	if (misResultCode::NoError != resultID)
		return resultID;
	auto founded = std::find(m_VolumeDataS.begin(), m_VolumeDataS.end(), volumedataDependency);
	if (founded == m_VolumeDataS.end())
	{
		m_VolumeDataS.push_back(volumedataDependency);
	}

	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::AddNextVolumedata(misUID pVolumedata, misUID parrentImageUID, misObjectVisibilityMap visibleParts)
{
	auto newVolumedataDependency = std::make_shared<misVolumeDataDependensies>();
	newVolumedataDependency->SetParentImageUID(parrentImageUID);
	newVolumedataDependency->SetObjectUID(pVolumedata);
	newVolumedataDependency->SetAllObjectVisibility(visibleParts);
	auto resultID = AddNextVolumedata(newVolumedataDependency);
	return resultID;
}

misResultCode::ResultIds misSimpleDataPackage::UpdateImageSDataPointer(ImageListTypedef imagePointerList)
{
	// Note : it shows it has not been set throw the SetImageDependencyTransform or SetVolumeDependencyTransform
	// Note : it must reset on every request for update Data Pointers
	m_NaturalPackageUsability = false;

	for (auto internalItr : m_ImageDataS)
	{
		internalItr->SetImage(0);
		auto currentImageUID = internalItr->GetObjectUID();
		for (auto newListItr = imagePointerList.begin(); newListItr != imagePointerList.end(); newListItr++)
		{
			auto imageUID = (*newListItr)->GetUID();
			if (imageUID == currentImageUID)
			{
				internalItr->SetImage(*newListItr);
				internalItr->SetName((*newListItr)->GetName());
				if ((*newListItr)->GetConfirmedDirection())
				{
					m_NaturalPackageUsability = true;
				}
				break;
			}
		}
	}
	return	 misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::
UpdateImageContainedPolyDataSDataPointer(ImageContainedPolyDataListTypedef imagePointerList)
{
	for (const auto& containd : m_ImageContaineds)
	{
		auto currentImageUID = containd->GetParentUID();
		auto found = std::find_if(imagePointerList.begin(), imagePointerList.end(),
			[&currentImageUID](auto containedPoly)
		{
			if (currentImageUID == containedPoly->GetParentImageUID())
				return true;
			return false;

		});
		if (found != imagePointerList.end())
		{
			(*found)->CopyAllSegmentedObjectToNewStructure();
			containd->SetImageContained(*found);
		}
	}

	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::UpdateVolumeSDataPointer(VolumeDataListTypedef* volumeDataPointerList)
{
	misResultCode::ResultIds  resultID;
	// for each GetVolume() data in the package: note: in this package at last only one is exist
	std::for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto volumeDep)
	{
		auto currentVolumedataUID = volumeDep->GetParentImageUID();
		volumeDep->SetVolume(NULL);
		// find corresponded GetVolume() data from dataset manger
		std::for_each(volumeDataPointerList->begin(), volumeDataPointerList->end(),
			[&](std::shared_ptr<IVolumeData> extractedVolumeData)
		{
			auto databaseVolumedataUID = extractedVolumeData->GetParentImageUID()/*GetUID()*/;
			if (0 == databaseVolumedataUID.compare(currentVolumedataUID))
			{
				volumeDep->SetVolume(extractedVolumeData);
				UpdateVolumesParrentImagePointer();
				return;
			}
		});
	});
	resultID = misResultCode::NoError;
	return	 resultID;
}

void misSimpleDataPackage::UpdateVolumesParrentImagePointer()
{
	for (auto volumeDep : m_VolumeDataS)
	{
		auto parrentImageUID = volumeDep->GetParentImageUID();
		volumeDep->SetImage(NULL);
		for (auto imageDep : m_ImageDataS)
		{
			if (imageDep->GetObjectUID() == parrentImageUID)
			{
				volumeDep->SetImage(imageDep->GetImage());
				break;
			}
		}
	}
}

misResultCode::ResultIds   misSimpleDataPackage::SetPolyDataDependencies(PolyDataDependencyListTypes* polydataSDependencies)
{
	if (polydataSDependencies)
	{
		m_PolydataS = polydataSDependencies;
	}
	else
	{
		return misResultCode::ErEmptyPointer;
	}
	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::SetImageDataDependencies(const ImageDependencyListTypes& imageDataSDependencies)
{
	if (!imageDataSDependencies.empty())
	{
		m_ImageDataS = imageDataSDependencies;
	}
	else
	{
		return misResultCode::ErEmptyPointer;
	}
	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::SetImageContainedPolyDataDependencies(
	ImageContainedPolydataDependencyListTypes imageDataSDependencies)
{
	m_ImageContaineds = imageDataSDependencies;
	return misResultCode::NoError;
}

void misSimpleDataPackage::SetVolumeDataDependencies(VolumeDataDependencyListTypes volumeDataSDependencies)
{
	m_VolumeDataS = volumeDataSDependencies;
}

ImageDependencyListTypes misSimpleDataPackage::GetImageDataDependencies() const
{
	return m_ImageDataS;
}

ImageContainedPolydataDependencyListTypes misSimpleDataPackage::GetImageContainedPolydataDependencies(void) const
{
	return m_ImageContaineds;
}

PolyDataDependencyListTypes misSimpleDataPackage::GetPolyDataDependencies() const
{
	PolyDataDependencyListTypes polyDatas;
	if (m_PolydataS)
	{
		polyDatas = *m_PolydataS;
	}
	return polyDatas;
}

VolumeDataDependencyListTypes misSimpleDataPackage::GetVolumeDataDependencies() const
{
	return m_VolumeDataS;
}

misResultCode::ResultIds misSimpleDataPackage::UpdateVolumedata(misUID pVolumedata, misObjectVisibilityMap visibleParts)
{
	for (auto volume : m_VolumeDataS)
	{
		if (volume->GetObjectUID() == pVolumedata)
		{
			volume->SetAllObjectVisibility(visibleParts);
			return misResultCode::NoError;
		}
	}
	return misResultCode::ErUnableTOAddInList;
}
std::shared_ptr<PlanDataListDependencyTypedef> misSimpleDataPackage::GetPlanDataDependencies(void)
{
	auto rels = std::make_shared<PlanDataListDependencyTypedef>();
	for (auto const& rel : m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID))
	{
		rels->push_back(std::dynamic_pointer_cast<parcast::IPackagePlanRel>(rel));
	}
	return rels;
}

std::shared_ptr<misSimpleDataPackage> misSimpleDataPackage::NewEmptyDataPackage()
{
	auto smartPtr = std::make_shared<misSimpleDataPackage>(
		misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
	smartPtr->SetObjectUID("");
	return smartPtr;
}


misLandmarkListTypdef misSimpleDataPackage::GetLandMarkPoints()
{
	misLandmarkListTypdef pointlist;
	if (m_LandMark)
		pointlist = m_LandMark->GetPoints();
	return pointlist;
}

misLandMarkBase* misSimpleDataPackage::GetLandMarkPointer()
{
	if (m_LandMark)
		return m_LandMark;
	return 0;
}

bool misSimpleDataPackage::SetLandMarkPoints(misLandmarkListTypdef landMarkPoints)
{
	if (m_LandMark)
	{
		m_LandMark->SetPoints(landMarkPoints);
		return true;
	}
	return false;
}

misUID misSimpleDataPackage::GetMainImageUID() const
{
	if (GetMainImage())
	{
		return GetMainImage()->GetUID();
	}
	return "";
}

std::shared_ptr<ICompeleteImageDependencies>  misSimpleDataPackage::GetMainImageProperites() const
{
	auto mainImageUID = GetMainImageUID();
	if (mainImageUID == "")
		return 0;

	for (auto iter : m_ImageDataS)
	{
		auto currentImageUID = iter->GetObjectUID();
		if (0 == currentImageUID.compare(mainImageUID))
		{
			auto pImageDep = std::make_shared<misCompeleteImageDependencies>();
			pImageDep->SetOpacity(iter->GetOpacity());
			pImageDep->SetObjectUID(iter->GetObjectUID());
			pImageDep->SetVisibility(iter->GetVisibility());
			pImageDep->SetImage(iter->GetImage());
			return pImageDep;
		}
	}
	return 0;
}

misResultCode::ResultIds misSimpleDataPackage::SetImageContainedPolyData(misUID mianImageUID)
{
	auto res = misResultCode::ErEmptyList;
	bool visibility = false;

	if (m_ImageContaineds.size() > 0)
	{
		res = misResultCode::ErUnableToFindInList;
		ImageContainedPolydataDependencyListTypes::iterator iter;
		for (iter = m_ImageContaineds.begin(); iter != m_ImageContaineds.end(); iter++)
		{
			if (mianImageUID == (*iter)->GetObjectUID())
			{
				visibility = true;
				res = misResultCode::NoError;
			}
		}

		// in bad condition set the first as a Main Image
		if (false == visibility)
		{
			res = misResultCode::NoError;
		}
	}
	return res;
}

MisObjectType misSimpleDataPackage::FindObjectType(misUID objectUID)
{
	if (true == IsImageType(objectUID))
	{
		return misImageType;
	}
	if (true == IsSegmentedType(objectUID))/*else if (true == IsPolyDataType(objectUID))*/
	{
		return misPolyDataType;
	}
	if (true == IsPlanType(objectUID))
	{
		return misPlanDataType;
	}
	if (true == IsVolumeType(objectUID))
	{
		return misVolumeDataType;
	}
	return misUnKnowObjectType;
}

bool misSimpleDataPackage::IsImageType(misUID &objectUID) const
{
	for (auto imageIter : m_ImageDataS)
	{
		auto currentImageUID = imageIter->GetObjectUID();
		if (0 == objectUID.compare(currentImageUID))
		{
			return true;
		}
	}
	return false;
}

bool misSimpleDataPackage::IsPolyDataType(misUID &objectUID)
{
	PolyDataDependencyListTypes::iterator polyIter;
	misCompeletePolyDataDependensiesStrct polydataStr;
	for (polyIter = m_PolydataS->begin(); polyIter != m_PolydataS->end(); polyIter++)
	{
		polydataStr = *polyIter;
		auto currentPolydatUID = polydataStr.objectUID;
		if (0 == objectUID.compare(currentPolydatUID))
		{
			return true;
		}
	}
	return false;
}

bool misSimpleDataPackage::IsSegmentedType(misUID &objectUID)
{
	for (const auto ImageContainedIter : m_ImageContaineds)
	{
		auto tempContained = ImageContainedIter->GetImageContained();
		if (tempContained)
		{
			if (tempContained->IsSpecificImageExisted(objectUID))
			{
				return true;
			}
		}
	}
	return false;
}

bool misSimpleDataPackage::IsPlanType(misUID &objectUID)
{
	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);
	for (auto const& rel : rels)
	{
		if (rel->GetPlanEntity()->GetUID() == objectUID)
		{
			return true;
		}
	}
	return false;
}

bool misSimpleDataPackage::IsVolumeType(misUID &objectUID)
{
	bool result = false;
	std::for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto volumeStr)
	{
		auto volumeData = volumeStr->GetVolume();
		if (volumeData)
		{
			auto volumeType = volumeData->GetObjectType(objectUID);
			if (volumeData->IsExistObject(volumeType))
			{
				result = true;
				return;
			}
		}
	});
	return result;
}

misResultCode::ResultIds misSimpleDataPackage::SetImagedataOpacity(misUID objectUID, double opacity)
{
	auto res = misResultCode::ErUnableToFindInList;
	for (auto& imageStruct : m_ImageDataS)
	{
		auto CurrentImageID = imageStruct->GetObjectUID();
		if (0 == objectUID.compare(CurrentImageID))
		{
			imageStruct->SetOpacity(opacity);
			res = misResultCode::NoError;
		}
	}
	return res;
}

void misSimpleDataPackage::SetImagedataVisibility(misUID objectUID, bool visible)
{
	for (auto& imageStruct : m_ImageDataS)
	{
		auto CurrentImageID = imageStruct->GetObjectUID();
		if (0 == objectUID.compare(CurrentImageID))
		{
			imageStruct->SetVisibility(visible);
		}
	}
}

misResultCode::ResultIds misSimpleDataPackage::SetPolydataVisibility(
	misUID objectContainerUID, misUID objectUID, bool visible, misPresentationDimension presentationDim)
{
	auto res = misResultCode::ErUnableToFindInList;
	for (auto imageCotained : m_ImageContaineds)
	{
		auto currentContainerUID = imageCotained->GetImageContained()->GetUID();
		if (currentContainerUID != objectContainerUID)
			continue;
		if (!imageCotained->HasVisibilityProperties(objectUID))
			continue;
		if (presentationDim == twoDimension)
			imageCotained->Set2dVisibility(objectUID, visible);
		else if (presentationDim == threeDimension)
			imageCotained->Set3dVisibility(objectUID, visible);
		res = misResultCode::NoError;
	}
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetVolumedataVisibility(
	misUID objectContainerUID, misUID objectUID, bool visible, misPresentationDimension presentationDim)
{
	auto res = misResultCode::ErUnableToFindInList;
	for (auto volumeIter : m_VolumeDataS)
	{
		if (!volumeIter->GetVolume())
			continue;

		auto currentVolumeUID = volumeIter->GetVolume()->GetUID();
		if (currentVolumeUID != objectContainerUID)
			continue;
		auto objVisibility = volumeIter->GetAllObjectVisibility();
		for (int i = 0; i < objVisibility.size(); i++)
		{
			bool set = volumeIter->SetObjectVisibility(objectUID, presentationDim, visible);
			if (set)
			{
				res = misResultCode::NoError;
				break;
			}
		}
	}
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetPlandataVisibility(
	misUID objectContainerUID, misUID objectUID, bool visible, misPresentationDimension presentationDim)
{
	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);

	for (auto& rel : rels)
	{
		auto plan = rel->GetPlanEntity();
		if (objectContainerUID != plan->GetParentImageUID())
			continue;
		if (plan->GetUID() != objectUID)
			continue;
		auto visibility = rel->GetVisibility();
		if (twoDimension == presentationDim)
			visibility.visibilityIn2DScene = visible;
		if (threeDimension == presentationDim)
			visibility.SetVisibilityIn3DScene(visible);

		rel->SetVisibility(visibility);
	}
	return misResultCode::NoError;
}

void misSimpleDataPackage::SetObjectOpacity(misUID objectContainerUID, misUID objectUID, double opacity)
{
 
	auto objectType = FindObjectType(objectUID);
	switch (objectType)
	{
	case misPolyDataType:
		SetPolydataOpacity(objectContainerUID, objectUID, opacity);
		break;

	case misVolumeDataType:
		SetVolumedataOpacity(objectContainerUID, objectUID, opacity);
		break;
	}

 
}

misResultCode::ResultIds misSimpleDataPackage::SetPolydataOpacity(misUID objectContainerUID, misUID objectUID,
	double opacity)
{
	auto res = misResultCode::ErUnableToFindInList;

	for (auto imageDepnedency : m_ImageContaineds)
	{
		auto currentVolumedataUID = imageDepnedency->GetImageContained()->GetUID();
		if (currentVolumedataUID == objectContainerUID)
		{
			imageDepnedency->SetOpacity(objectUID, opacity);
			res = misResultCode::NoError;
		}
	}
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetVolumedataOpacity(misUID objectContainerUID, misUID objectUID, double opacity)
{
	auto res = misResultCode::ErUnableToFindInList;
	for (auto volumeIter : m_VolumeDataS)
	{
		if (!volumeIter->GetVolume())
			continue;
		auto currentVolumedataUID = volumeIter->GetVolume()->GetUID();
		if (currentVolumedataUID == objectContainerUID)
		{
			auto objVisibility = volumeIter->GetAllObjectVisibility();
			for (int i = 0; i < objVisibility.size(); i++)
			{
				bool set2D = volumeIter->SetObjectOpacity(objectUID, twoDimension, opacity);
				bool set3D = volumeIter->SetObjectOpacity(objectUID, threeDimension, opacity);
				if (set2D && set3D)
				{
					res = misResultCode::NoError;
					break;
				}
			}
		}
	}
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetPlandataOpacity(misUID objectContainerUID, misUID objectUID, double opacity)
{
	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);

	for (auto& rel : rels)
	{
		auto plan = rel->GetPlanEntity();
		if (objectContainerUID != plan->GetParentImageUID())
			continue;
		if (plan->GetUID() != objectUID)
			continue;
		auto visibility = rel->GetVisibility();
		visibility.SetOpacityIn2DScene(visibility.OpacityIn3DScene = opacity);
		rel->SetVisibility(visibility);
	}

	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::SetObjectColor(misUID objectUID, misColorStruct color)
{
	misResultCode::ResultIds res;
	res = misResultCode::ErUnableToFindInList;

	auto objectType = FindObjectType(objectUID);
	switch (objectType)
	{
	case misPolyDataType:
		res = SetPolydataColor(objectUID, color);
		break;

	case misVolumeDataType:
		res = SetVolumedataColor(objectUID, color);
		break;

	case misPlanDataType:
		res = SetPlandataColor(objectUID, color);
		break;
	}

	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetPolydataColor(misUID objectUID, misColorStruct color)
{
	auto res = misResultCode::ErUnableToFindInList;
	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto tempStruct)
	{
		tempStruct->SetObjectColor(objectUID, color);
		res = misResultCode::NoError;
		return;
	});
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetVolumedataColor(misUID objectUID, misColorStruct color)
{
	auto res = misResultCode::ErUnableToFindInList;
	for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto tempStruct)
	{
		if (!tempStruct->GetVolume())
			return;
		mis3DModelObjectOpacityPropertiesStrct modelProp;
		bool found = tempStruct->GetObjectVisibilityProperties(objectUID, modelProp);
		if (found)
		{
			auto volumeType = tempStruct->GetVolume()->GetObjectType(objectUID);
			tempStruct->GetVolume()->SetObjectColor(volumeType, color);
			res = misResultCode::NoError;
			return;
		}
	});
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::SetPlandataColor(misUID objectUID, misColorStruct color)
{
	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);
	for (auto& rel : rels)
	{
		auto plan = rel->GetPlanEntity();
		if (plan->GetUID() != objectUID)
			continue;

		plan->SetPlannigColor(color);

	}

	return misResultCode::NoError;
}

int misSimpleDataPackage::GetNumberOfImages() const
{
	return m_ImageDataS.size();
}

int misSimpleDataPackage::GetNumberOf3DModels()
{
	int polySize = m_PolydataS->size();
	int volumeSize = m_VolumeDataS.size();
	return polySize + volumeSize;
}

size_t misSimpleDataPackage::GetNumberOfPlanes() const
{
	return m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID).size();
}









bool misSimpleDataPackage::FindUsability(misUID parrentImageUID)
{
	bool finalUsability = m_NaturalPackageUsability | m_ForcedPackageUseability;
	return finalUsability;
}

misResultCode::ResultIds misSimpleDataPackage::AddingValidityStatus(misUID newObjectParrentUID)
{
	auto MainImageUID = GetMainImageUID();
	auto res = misResultCode::NoError;
	if (0 != MainImageUID.compare(""))
	{
		if (0 != MainImageUID.compare(newObjectParrentUID))
		{
			res = misResultCode::ErDifferenetParrentForHP;
		}
	}
	return res;
}

misShortImageViewingStrct misSimpleDataPackage::GetImageDataProperties(misUID objectUID)
{
	misShortImageViewingStrct pImageStr;
	ImageDependencyListTypes::iterator imageIter;
	for (auto imageIter : m_ImageDataS)
	{
		if (objectUID == imageIter->GetObjectUID())
		{
			pImageStr.name = imageIter->GetName();
			pImageStr.opacity = imageIter->GetOpacity();
			pImageStr.visibility = imageIter->GetVisibility();
		}
	}
	return pImageStr;
}

misShort3DModelViewingStrct misSimpleDataPackage::Get3DModelDataProperties(misUID objectContainerUID, misUID objectUID)
{
	misShort3DModelViewingStrct pPolyDataStr;
	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto tempImageContained)
	{
		if (tempImageContained->GetImageContained())
		{
			if (0 == objectContainerUID.compare(tempImageContained->GetImageContained()->GetUID()))
			{
				if (tempImageContained->HasVisibilityProperties(objectUID))
				{
					ImagePolyDataContenStrct tempStrct =
						tempImageContained->GetImageContained()->GetOLDPolyDataProperties(objectUID);
					pPolyDataStr.objectUID = objectUID;
					pPolyDataStr.objectContainerUID = objectContainerUID;
					pPolyDataStr.parentImageUID = tempImageContained->GetImageContained()->GetParentImageUID();
					pPolyDataStr.color = tempStrct.PolyDataColor;
					pPolyDataStr.name = tempStrct.PolyDataName;
					pPolyDataStr.volume = tempStrct.ObjectVolume;
					pPolyDataStr.opacity = tempStrct.OpacityProp.GetOpacityIn2DScene();
					pPolyDataStr.visibility3D = tempStrct.OpacityProp.GetVisibilityIn3DScene();
					pPolyDataStr.segmentedObjectVisibility = tempStrct.OpacityProp.visibilityIn2DScene;
					pPolyDataStr.renderingType = misSurfaceRendering;
					pPolyDataStr.type = misTumor;
					pPolyDataStr.objectMarginAlarm = tempImageContained->GetImageContained()->GetAlarmMargin(objectUID);
					pPolyDataStr.objectShowMargin = tempImageContained->GetImageContained()->GetShowMarginRegion(objectUID);
					pPolyDataStr.objectMarginValue = tempImageContained->GetImageContained()->GetMarginValue(objectUID);
				}
			}
		}
	});
	for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto tempVolumeData)
	{
		if (tempVolumeData->GetVolume())
		{
			if (0 == objectContainerUID.compare(tempVolumeData->GetVolume()->GetUID()))
			{
				mis3DModelObjectOpacityPropertiesStrct modelProp;
				bool found = tempVolumeData->GetObjectVisibilityProperties(objectUID, modelProp);
				if (found)
				{
					auto volumeType = tempVolumeData->GetVolume()->GetObjectType(objectUID);
					auto tempStrct = tempVolumeData->GetVolume()->GetObjectProperties(volumeType);

					pPolyDataStr.objectUID = objectUID;
					pPolyDataStr.objectContainerUID = objectContainerUID;
					pPolyDataStr.parentImageUID = tempVolumeData->GetVolume()->GetParentImageUID();
					pPolyDataStr.opacity = tempStrct.visibilityProp.OpacityIn3DScene;
					pPolyDataStr.color = tempStrct.volumeColor;
					pPolyDataStr.name = tempStrct.Name;
					pPolyDataStr.visibility3D = tempStrct.visibilityProp.GetVisibilityIn3DScene();
					pPolyDataStr.segmentedObjectVisibility = tempStrct.visibilityProp.visibilityIn2DScene;
					pPolyDataStr.renderingType = misVolumeRendering;

					if (volumeType == misVolumeViewingTypes::misBoneViwing)
					{
						pPolyDataStr.type = misBone;
					}
					else if (volumeType == misVolumeViewingTypes::misSkinviewing)
					{
						pPolyDataStr.type = misSkin;
					}
					else if (volumeType == misVolumeViewingTypes::misMetalViewing)
					{
						pPolyDataStr.type = misMetal;
					}
				}
			}
		}
	});

	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);
	for (auto const& rel : rels)
	{
		auto plan = rel->GetPlanEntity();
		if (objectUID == plan->GetUID())
		{
			pPolyDataStr.color = plan->GetPlannigColor();
			pPolyDataStr.name = plan->GetPlanName();
			pPolyDataStr.objectUID = plan->GetUID();
			auto visibility = rel->GetVisibility();
			pPolyDataStr.visibility3D = visibility.GetVisibilityIn3DScene();
			pPolyDataStr.opacity = visibility.OpacityIn3DScene;
			pPolyDataStr.segmentedObjectVisibility = visibility.visibilityIn2DScene;
			continue;
		}

		pPolyDataStr.objectContainerUID = objectContainerUID;
		pPolyDataStr.parentImageUID = plan->GetParentImageUID();
	}
	return pPolyDataStr;
}

misShortPlanningViewingStruct misSimpleDataPackage::GetPlanDataProperties(misUID objectUID)
{
	misShortPlanningViewingStruct props;
	auto rels = m_PackagePlanRelRepo->GetByPackageUid(m_DataObjectUID);
	for (auto const& rel : rels)
	{
		auto plan = rel->GetPlanEntity();
		if (objectUID != plan->GetUID())
			continue;
		props.name = plan->GetPlanName();
		props.color = plan->GetPlannigColor();
		props.visibility = rel->GetVisibility().GetVisibilityIn3DScene();

	}
	return props;
}

bool misSimpleDataPackage::Delete3DModel(misUID objectContainerUID, misUID ObjectUID)
{
	bool isDeleteDone = false;
	for (auto tempImageContained : m_ImageContaineds)
	{
		if (!tempImageContained->GetImageContained())
			continue;
		if (objectContainerUID != tempImageContained->GetImageContained()->GetUID())
			continue;

		tempImageContained->GetImageContained()->DeleteObjectForced(ObjectUID);
		auto res = DeleteSegmentedObject(ObjectUID, objectContainerUID);
		if (res == NOERROR)
			isDeleteDone = true;
	}
	for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto tempVolumeData)
	{
		if (!tempVolumeData->GetVolume())
			return;
		if (objectContainerUID != tempVolumeData->GetVolume()->GetUID())
			return;
		mis3DModelObjectOpacityPropertiesStrct modelProp;
		bool found = tempVolumeData->GetObjectVisibilityProperties(ObjectUID, modelProp);
		if (!found)
			return;
		auto volumeType = tempVolumeData->GetVolume()->GetObjectType(ObjectUID);
		tempVolumeData->GetVolume()->DeleteObject(volumeType);
		auto res = DeleteRenderingObject(ObjectUID, objectContainerUID);
		if (res == NOERROR)
			isDeleteDone = true;
	});
	auto res = DeletePlanData(ObjectUID);
	if (res == NOERROR)
		isDeleteDone = true;
	return isDeleteDone;
}

void misSimpleDataPackage::SetObjectVisibility(
	misUID objectContainerUID, misUID objectUID, bool isVisible, misPresentationDimension presentationDim)
{

	MisObjectType objectType = FindObjectType(objectUID);

	switch (objectType)
	{
	case misPolyDataType:
		SetPolydataVisibility(objectContainerUID, objectUID, isVisible, presentationDim);
		break;

	case misVolumeDataType:
		SetVolumedataVisibility(objectContainerUID, objectUID, isVisible, presentationDim);
		break;

	case misPlanDataType:
		SetPlandataVisibility(objectContainerUID, objectUID, isVisible, presentationDim);
		break;
	case misImageType:
		SetImagedataVisibility(objectUID, isVisible);
		break;

	}
}

misResultCode::ResultIds misSimpleDataPackage::AddNextSegmentedData(
	misUID objectContainerUID, misUID parentImageUID, misObjectVisibilityMap newSegmentedObject)
{
	auto res = misResultCode::NoError;
	auto checkDuplicateRes = AddNextImageContainedPolydata(objectContainerUID, parentImageUID);

	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto& completeImageContainedStrct)
	{
		misObjectVisibilityMap::iterator it;

		if (completeImageContainedStrct->GetImageContained())
		{
			if (objectContainerUID == completeImageContainedStrct->GetImageContained()->GetUID())
			{
				it = newSegmentedObject.begin();
				if (it == newSegmentedObject.end())
				{
					res = misResultCode::ErEmptyList;
					return;
				}
				else // if UID is matched and map has valid information
				{
					//check duplicate
					auto tempUID = it->first;
					if (completeImageContainedStrct->GetAllObjectVisibility().end() !=
						completeImageContainedStrct->GetAllObjectVisibility().find(tempUID))
					{
						res = misResultCode::ErDuplicatedObjectNotPermitable;
						return;
					}
					else //insert to map
					{
						completeImageContainedStrct->GetAllObjectVisibility().insert(misObjectVisibilityPair(it->first, it->second));
					}
				}
			}
			else
			{
				res = misResultCode::ErPolyDataNotExist;
			}
		}
	});
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::DeleteSegmentedObject(misUID segmentedObjUID, misUID objectContainerUID)
{
	auto res = misResultCode::ErXXXUnknownError;
	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto completeImageContainedStrct)
	{
		if (completeImageContainedStrct->GetImageContained())
		{
			misObjectVisibilityMap::iterator it;
			if (objectContainerUID == completeImageContainedStrct->GetImageContained()->GetUID())
			{
				//find the corresponding pair in the map
				if (completeImageContainedStrct->HasVisibilityProperties(segmentedObjUID))
				{
					completeImageContainedStrct->RemoveObjcteVisibility(segmentedObjUID);
					res = misResultCode::NoError;
				}
				else // this segmented object is not existed in map
				{
					res = misResultCode::ErPolyDataNotExist;
				}
			}
		}
	});

	return res;
}

misResultCode::ResultIds misSimpleDataPackage::DeleteRenderingObject(misUID renderedUID, misUID volumedataUID)
{
	auto res = misResultCode::ErXXXUnknownError;
	for_each(m_VolumeDataS.begin(), m_VolumeDataS.end(),
		[&](auto completeVolumeDataStrct)
	{
		if (!completeVolumeDataStrct->GetVolume())
			return;
		if (volumedataUID == completeVolumeDataStrct->GetVolume()->GetUID())
		{
			if (completeVolumeDataStrct->GetAllObjectVisibility().empty())
				res = misResultCode::ErEmptyList;
			else
			{
				mis3DModelObjectOpacityPropertiesStrct modelProp;
				bool found = completeVolumeDataStrct->GetObjectVisibilityProperties(renderedUID, modelProp);
				if (found)
				{
					completeVolumeDataStrct->DeleteObjectVisibility(renderedUID);
					res = misResultCode::NoError;
				}
				else // this segmented object is not existed in map
					res = misResultCode::ErPolyDataNotExist;
			}
		}
	});
	return res;
}

misResultCode::ResultIds misSimpleDataPackage::ResetPackage()
{
	if (!m_ImageDataS.empty())
		m_ImageDataS.clear();
	m_ImageContaineds.clear();
	m_PackagePlanRelRepo->DeleteByPackageUid(m_DataObjectUID);
	m_ForcedPackageUseability = false;
	m_NaturalPackageUsability = false;
	return misResultCode::NoError;
}
std::vector<itk::Point<double, 3>> misSimpleDataPackage::GetParametricSpline() const
{
	return m_ParametricSpline;
}

void misSimpleDataPackage::SetParametricSpline(const std::vector<itk::Point<double, 3>>& val)
{
	m_ParametricSpline = val;
}

misResultCode::ResultIds misSimpleDataPackage::InvisibleAllPlanDatas()
{
	return misResultCode::NoError;
}

misResultCode::ResultIds misSimpleDataPackage::SetMarginAlaram(misUID containerUID, misUID SegmentedObjectUID, bool val)
{
	auto res = misResultCode::NoError;
	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto tempImageContained)
	{
		if (tempImageContained->GetImageContained())
		{
			if (0 == containerUID.compare(tempImageContained->GetImageContained()->GetUID()))
			{
				tempImageContained->SetAlarmMargin(SegmentedObjectUID, val);
			}
			else
				res = misResultCode::ErEmptyObjectUID;
		}
		else
		{
			res = misResultCode::ErNoValidPointer;
		}
	});

	return res;
}

misResultCode::ResultIds misSimpleDataPackage::ShowMarginRegion(misUID containerUID, misUID SegmentedObjectUID, bool val)
{
	auto res = misResultCode::NoError;
	for_each(m_ImageContaineds.begin(), m_ImageContaineds.end(),
		[&](auto tempImageContained)
	{
		if (tempImageContained->GetImageContained())
		{
			if (0 == containerUID.compare(tempImageContained->GetImageContained()->GetUID()))
			{
				tempImageContained->ShowMarginRegion(SegmentedObjectUID, val);
			}
			else
				res = misResultCode::ErEmptyObjectUID;
		}
		else
		{
			res = misResultCode::ErNoValidPointer;
		}
	});

	return res;
}

void misSimpleDataPackage::DeleteAllLandmarks()
{
	m_LandMark->DeleteAllPoints();
}

std::shared_ptr<IImage> misSimpleDataPackage::GetMainImage() const
{
	const auto  imagePriory = ImagePriorty(m_ImageDataS);
	return imagePriory.GetMainImage();
}


std::vector<std::shared_ptr<IImage>> misSimpleDataPackage::GetImages() const
{
	std::vector<std::shared_ptr<IImage>> result;
	for (const auto imageDep : m_ImageDataS)
	{
		if (imageDep->GetImage())
		{
			result.push_back(imageDep->GetImage());
		}
	}
	return result;
}

void misSimpleDataPackage::SetCSCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val)
{
}

std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > misSimpleDataPackage::GetCSCorrelationManager() const
{
	return m_CSCorrelationManager;
}

void misSimpleDataPackage::SetObjectUID(const misUID& dataUID)
{
	if (!m_UIDSetOccurance)
	{
		m_UIDSetOccurance++;
		m_DataObjectUID = dataUID;
	}
}

misUID misSimpleDataPackage::GetObjectUID() const
{
	return m_DataObjectUID;
}

void misSimpleDataPackage::SetName(std::string name)
{
	m_Name = name;
}

std::string misSimpleDataPackage::GetName() const
{
	return m_Name;
}

void misSimpleDataPackage::CreateVolumeFromImage(std::shared_ptr<IImage> image, double threshold, misApplicationType appType)
{
	SetImageToRelatedImageDataDependancy(image);
	UpdateImageSDataPointer(misDatasetManager::GetInstance()->GetImages());
	if (!GetVolumeDataDependencies().empty())
		DeleteAllVolumedatas();
	const auto volumeStructData = m_VolumeFactory->CreateTemporaryVolumeDependency(threshold, image, appType);
	AddNextVolumedata(volumeStructData);
}



std::shared_ptr<PlanDataListTypedef> misSimpleDataPackage::ExtractPlansListFromPackage()
{
	auto palnDependency = GetPlanDataDependencies();
	auto plansList = std::make_shared<PlanDataListTypedef>();
	std::for_each(palnDependency->cbegin(), palnDependency->cend(), [&](auto packagePlan)
	{
		plansList->push_back(std::dynamic_pointer_cast<misPlanData>(packagePlan->GetPlanEntity()));
	});
	return plansList;
}
std::string  misSimpleDataPackage::GetFlyzoneStatus(const double* position)
{
	std::vector<PropertiesOfPixelInImageType> FlyZoneStatus;
	for (int i = 0; i < m_ImageContaineds.size(); i++)
		FlyZoneStatus.push_back(m_ImageContaineds[i]->GetImageContained()->GetPixelData(position));
	std::string segmentationRegion;
	for (int i = 0; i < FlyZoneStatus.size(); i++)
	{
		for (int j = 0; j < FlyZoneStatus[i].size(); j++)
		{
			if (FlyZoneStatus[i][j].pixelType != misBackground)
			{
				segmentationRegion.append("Object: ");
				segmentationRegion.append(FlyZoneStatus[i][j].PolyDataName);
				segmentationRegion.append(misEnumUtilities::ConvertFlyZoneTypeEnumToString(FlyZoneStatus[i][j].pixelType));
			}
		}
	}
	return segmentationRegion;
}
