#include "StdAfx.h"
#include "misDataSetManagerUtilities.h"

#include "misCompositeDataPackage.h"
#include "misEnumUtilities.h"
#include "misMaskImageData.h"
#include "misStringTools.h"
#include "misSimpleDataPackage.h"


using std::string;
using std::stringstream;
using std::vector;

misDataSetManagerUtilities::misDataSetManagerUtilities(void)
{
}

misDataSetManagerUtilities::~misDataSetManagerUtilities(void)
{
}

bool     misDataSetManagerUtilities::FindDuplicatedPackageInDatasetManager (PackagesListTypedef packageList, misUID  packageUID)
{
	PackagesListTypedef::iterator   listIterator;
	std::shared_ptr<ISimpleDataPackage>         pacakgePointer;

	for(listIterator = packageList.begin(); listIterator != packageList.end(); listIterator++)
	{
		pacakgePointer = (*listIterator);


		if (0 == packageUID.compare(pacakgePointer->GetObjectUID()) )
		{
			// there is duplicated Image
          return true;
		}
	}
	return false;
}

bool misDataSetManagerUtilities::FindDuplicatedImageInDataset( ImageListTypedef imageList, misUID imagePrimeryUID )
{
	for(auto listItr = imageList.begin(); listItr != imageList.end(); listItr++)
	{
		auto seriesUID = (*listItr)->GetPrimeryUID();
		if (seriesUID == imagePrimeryUID)
			return true;
	}
	return false;
}

string   misDataSetManagerUtilities::MakeBinaryFileName(MisObjectType objectType, int objectNumber)
{
	std::string  binaryName;
	std::string StrImageNumber;

	if (misImageType == objectType)
	{
		binaryName.append("image");
	}
	else if	(misPolyDataType == objectType)
	{
		binaryName.append("PloyData");
	}
	else if	(misImageContainedPolydataType == objectType)
	{
		binaryName.append("Segment");
	}

	StrImageNumber =  misStringTools::IntToString(objectNumber) ;
	binaryName.append(StrImageNumber);
	binaryName.append(".");

	string date;
	date = misStringTools::GetCurrentDatePlusTime();
	binaryName.append(date);

	return binaryName;

}

bool misDataSetManagerUtilities::FindDuplicatedVolumeDataInDataset(VolumeDataListTypedef* volumedataList, misUID volumeDataUID, 
	misUID parrentImageUID)
{
	auto res = std::find_if(volumedataList->cbegin(), volumedataList->cend(), [&](auto volume) -> bool
	{
		return volume->GetParentImageUID() == volumeDataUID || volume->GetParentImageUID() == parrentImageUID;
	});
	return res != volumedataList->cend();
}

 
void misDataSetManagerUtilities::UpdatePackageNames( PackagesListTypedef packageList )
{
	UpdateSimplePackageNames(packageList);
	UpdateCompositePackageNames(packageList);
}

std::string misDataSetManagerUtilities::GetPackageName( misImageDataModality Imagemodality, int counter )
{
	std::string  packageName = "";
	packageName.append(misEnumUtilities::ConvertImageModalityEnumToString(Imagemodality));	
	stringstream ss;
	ss <<counter;
	string str = ss.str();
	packageName.append(str);

	return packageName;
}

PackagesListTypedef misDataSetManagerUtilities::UpdateSimplePackageNames( PackagesListTypedef packageList )
{
	PackagesListTypedef simplePackageList;
	int CTCounter = 0, MRICounter = 0, fMRICounter = 0;
	for(auto listIterator = packageList.begin(); listIterator != packageList.end(); listIterator++)
	{
		std::shared_ptr<misCompositeDataPackage> compositePack = 
			std::dynamic_pointer_cast<misCompositeDataPackage>(*listIterator);
		if(compositePack)
			continue;

		auto ImageProp = (*listIterator)->GetMainImageProperites();
		if(ImageProp && ImageProp->GetImage())
		{
			std::string  newPackageName = "";
			misImageDataModality imageModality = (*listIterator)->GetMainImageProperites()->GetImage()->GetImageModality();
			if (imageModality == CT)
			{
				CTCounter++;
				newPackageName = GetPackageName(imageModality, CTCounter);
			} 
			else if(imageModality == MRI)
			{
				MRICounter++;
				newPackageName = GetPackageName(imageModality, MRICounter);
			}
			else if(imageModality == fMRI)
			{
				fMRICounter++;
				newPackageName = GetPackageName(imageModality, fMRICounter);
			}

			if ((*listIterator)->GetName().empty())
			{
				if (MRICounter || CTCounter)
					(*listIterator)->SetName(newPackageName);
				else
					(*listIterator)->SetName("WrongModalityPackage");
			}

			if(!(MRICounter || CTCounter))
				(*listIterator)->SetName("WrongModalityPackage");

			simplePackageList.push_back((*listIterator));
		}
	}
	return simplePackageList;
}

void misDataSetManagerUtilities::UpdateCompositePackageNames( const PackagesListTypedef &packageList )
{
	auto simplePackageList = UpdateSimplePackageNames(packageList);
	std::for_each(packageList.cbegin(), packageList.cend(), [&] (std::shared_ptr<ISimpleDataPackage> package)
	{
		auto compositePack = std::dynamic_pointer_cast<misCompositeDataPackage>(package);
		if(!compositePack || !compositePack->GetMainImageProperites() || !compositePack->GetMainImageProperites()->GetImage())
			return;
		vector<misUID> imageUids = GetPackageImageUids(compositePack);
		vector<string> simplePackageNames = GetPackageNamesByImageUids(simplePackageList, imageUids);
		stringstream packageName;
		for (int i = 0; i < simplePackageNames.size(); i++)
		{
			packageName << simplePackageNames[i];
			if (i != simplePackageNames.size() - 1)
				packageName << "-";
		}
		compositePack->SetName(packageName.str());
	});			
	RenameDuplicateNames(packageList);
}			

std::vector<misUID> misDataSetManagerUtilities::GetPackageImageUids(std::shared_ptr<misCompositeDataPackage> compositePack)
{
	std::vector<string> imageUids;
	auto imageList = compositePack->GetImageDataDependencies();
	for (int i = 0; i < imageList.size(); i++)
		if (imageList[i]->GetImage())
			imageUids.push_back(imageList[i]->GetImage()->GetUID());
	return imageUids;
}

std::vector<misUID> misDataSetManagerUtilities::GetPackageNamesByImageUids(
	const PackagesListTypedef &simplePackageList, const std::vector<misUID> &imageUids)
{
	vector<misUID> packageImages;
	packageImages.reserve(imageUids.size());
	for (int i = 0; i < imageUids.size(); i++)
		for (auto simplePackage = simplePackageList.cbegin(); simplePackage != simplePackageList.cend(); ++simplePackage)
		{
			if (imageUids[i] == (*simplePackage)->GetMainImageUID())
			{
				packageImages.push_back((*simplePackage)->GetName());
				break;
			}
		}
	return packageImages;
}

void misDataSetManagerUtilities::RenameDuplicateNames(const PackagesListTypedef &packageList )
{
 	for(auto sourcePackage = packageList.cbegin(); sourcePackage != packageList.cend(); sourcePackage++)
	{
		std::string sourcePackageName = (*sourcePackage)->GetName();
		int autoIndex = 1;
		for(auto packageDest = sourcePackage + 1; packageDest != packageList.cend(); packageDest++ )
		{
			std::shared_ptr<misSimpleDataPackage> compositePack =
				std::dynamic_pointer_cast<misSimpleDataPackage>(*packageDest);
			if (compositePack)
				continue;

			std::string destinationPackageName = (*packageDest)->GetName();
			if (destinationPackageName == sourcePackageName)
			{
				if (autoIndex == 1)
				{
					stringstream sourceFormattedName;
					sourceFormattedName << sourcePackageName << "-" << autoIndex;
					(*sourcePackage)->SetName(sourceFormattedName.str());
				}
				autoIndex++;
				stringstream destFormattedName;
				destFormattedName << destinationPackageName << "-" << autoIndex;
				(*packageDest)->SetName(destFormattedName.str());
			}
		}
	}
}