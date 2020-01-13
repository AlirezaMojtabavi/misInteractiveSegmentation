#include "stdafx.h"
#include "..\Header\misVolumeRenderingStrategy.h"
#include "..\Header\misDataSetManager.h"
#include "..\Header\misImageToTextureMap.h"
#include "..\Header\misTransFunctionBuilder.h"
#include "misApplicationSetting.h"

misVolumeRenderingStrategy::misVolumeRenderingStrategy(ImageDependencyListTypes currentImageDataDependencies,
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, misVolumeViewingTypes volumeViewing,
	int numberOfSegmentedIMage)
	:m_CurrentImageDataDependencies(currentImageDataDependencies),
	m_CSCorrelationManager(correlationManager)
	, m_VolumeViewingType(volumeViewing),
	m_NumberOfSegmentedImage(numberOfSegmentedIMage)
	, m_DefaultVolumeData(std::make_shared<misVolumeData>())
{
	int mriCount = getNumberOfMriImages();
	if (AllImageAreMrAndSegmentedObjectExist())
		return;
	m_CTImage = FindFirtstCtImage();


	m_SelectedImage = GetSelctedImage();
	std::string imageUID = m_SelectedImage->GetUID();

	auto appType = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
	double threshold = m_SelectedImage->GetCurrentSkinThreshold().get();

	switch (appType)
	{
	case Spine:
		threshold = m_SelectedImage->GetCurrentBoneThreshold().get();
		if (m_VolumeViewingType == misVolumeViewingTypes::misBoneViwing)
			m_VolumeViewingType = misVolumeViewingTypes::misSpineViewing;
		break;
	case Dental:
		threshold = m_SelectedImage->GetCurrentTeethThreshold().get();
		break;
	case AnimalImaging:
		m_VolumeViewingType = misVolumeViewingTypes::misAnimalViewing;
	case CMF:
		threshold = m_SelectedImage->GetCurrentBoneThreshold().get();
		break;

	}
	m_DefaultVolumeData->SetMinThreshold(m_VolumeViewingType, threshold);
	m_DefaultVolumeData->SetComponentVisibilityAll();
	m_DefaultVolumeData->SetImageModality(m_SelectedImage->GetImageModality());
	m_DefaultVolumeData->SetParentImageUID(m_SelectedImage->GetUID());
}

bool misVolumeRenderingStrategy::AllImageAreMrAndSegmentedObjectExist()
{
	return getNumberOfMriImages() == m_CurrentImageDataDependencies.size() && GetNumberOfSegmentedImage() > 0;
}

std::shared_ptr<TransFuncIntensity> misVolumeRenderingStrategy::getTransferFunction(std::shared_ptr<IImage> image)
{
	auto opacityColorMappingLst = m_DefaultVolumeData->GetOpacityColorMap(threeDimension);
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto tex = TextureHandler->LookUpTexture(image);
	auto TableRange = tex->GetTableRange();
	misTransFunctionBuilder pTrasferfunction;
	return pTrasferfunction.GenerateTransferFunction(opacityColorMappingLst, TableRange);
}

std::shared_ptr<IImage> misVolumeRenderingStrategy::GetSelctedImage()
{
	if (FindFirtstCtImage())
		return m_CTImage;
	return m_CurrentImageDataDependencies[0]->GetImage();
}

std::shared_ptr<misVolumeData> misVolumeRenderingStrategy::getVolumeData() const
{
	return m_DefaultVolumeData;
}

int misVolumeRenderingStrategy::getNumberOfMriImages() const
{
	int mri_image_count = std::count_if(m_CurrentImageDataDependencies.cbegin(), m_CurrentImageDataDependencies.cend(),
		[&](const auto& imageDep) -> bool
	{
		if (!imageDep->GetImage())
			return false;
		if (imageDep->GetImage()->GetImageModality() == MRI)
			return true;
		return false;
	});
	return mri_image_count;
}

std::shared_ptr<IImage> misVolumeRenderingStrategy::FindFirtstCtImage() const
{
	for (auto imageDep : m_CurrentImageDataDependencies)
	{
		auto selectedImage = imageDep->GetImage();
		if (selectedImage && selectedImage->GetImageModality() == CT)
			return selectedImage;
	}
	return nullptr;
}

void misVolumeRenderingStrategy::SetVolumeViewingType(misVolumeViewingTypes volumeViewingType)
{
	m_VolumeViewingType = volumeViewingType;
}

int misVolumeRenderingStrategy::GetNumberOfSegmentedImage() const
{
	return m_NumberOfSegmentedImage;
}

void misVolumeRenderingStrategy::SetNumberOfSegmentedImage(int val)
{
	m_NumberOfSegmentedImage = val;
}