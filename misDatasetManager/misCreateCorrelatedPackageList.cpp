#include "stdafx.h"
#include "misCreateCorrelatedPackageList.h"
#include "misDatasetManager.h"
#include "ICoordinateSystemRepository.h"
#include "IImage.h"
#include "ISimpleDataPackage.h"
#include "ImagePriorty.h"

misCreateCorrelatedPackageList::misCreateCorrelatedPackageList(
    std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
        correlationMnager)
    : m_CSCorrelationManager(correlationMnager) {}

void misCreateCorrelatedPackageList::CreateCorrelatedPackageList()
{

	auto m_coordinates = misDatasetManager::GetInstance()->GetCSRepository()->GetAllCoordinatesSystems();
	for (auto sourceCoordinate = m_coordinates.begin(); sourceCoordinate != m_coordinates.end(); sourceCoordinate++)
	{
		auto sourceImage = std::dynamic_pointer_cast<IImage>(*sourceCoordinate);
		if (!sourceImage)
			continue;
		for (auto destinationCoordinate = sourceCoordinate + 1;
			destinationCoordinate != m_coordinates.end(); destinationCoordinate++)
		{
			auto destinationImage = std::dynamic_pointer_cast<IImage>(*destinationCoordinate);
			if (!destinationImage)
				continue;
			auto transfom = m_CSCorrelationManager->GetTransform((*sourceCoordinate)->GetUID(),
				(*destinationCoordinate)->GetUID());
			if (transfom->IsValid())
			{
				misCorrelatedImagesStr corrStr;
				auto sourceComp = std::make_shared<misCompeleteImageDependencies>();
				sourceComp->SetImage(sourceImage);
				auto destComp = std::make_shared<misCompeleteImageDependencies>();
				destComp->SetImage(destinationImage);
				const auto images = ImagePriorty::ImageDependencyListTypes{ sourceComp , destComp };
				ImagePriorty priorityImages(images);
					corrStr.FirstImageUID = priorityImages.GetMainImage()->GetUID();
					if(destinationImage->GetUID() == priorityImages.GetMainImage()->GetUID())
						corrStr.secondImageUID = sourceImage->GetUID();
					else
						corrStr.secondImageUID = destinationImage->GetUID();
				misDatasetManager::GetInstance()->AddNewPackageDataByCorrelatedImages(corrStr);
			}
		}
	}

	ClearUnCorrelatedPackage();
}

void misCreateCorrelatedPackageList::ClearUnCorrelatedPackage()
{

	auto packageData = misDatasetManager::GetInstance()->GetPackageDataS();
	for (auto package = packageData.begin(); package != packageData.end(); ++package)
	{
		std::string packageToRemove = "";
		auto images = (*package)->GetImages();
		for (auto imageSource = images.begin(); imageSource != images.end() && packageToRemove.empty(); ++imageSource)
		{
			for (auto imageDestination = imageSource + 1; imageDestination != images.end() && packageToRemove.empty();
				++imageDestination)
			{
				auto transfom = m_CSCorrelationManager->GetTransform((*imageSource)->GetUID(), (*imageDestination)->GetUID());
				if (!transfom->IsValid())
					packageToRemove = (*package)->GetObjectUID();
			}
		}
		if (!packageToRemove.empty())
			misDatasetManager::GetInstance()->RemovePackage(packageToRemove);
	}

}
