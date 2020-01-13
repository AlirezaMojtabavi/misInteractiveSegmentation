#include "stdafx.h"
#include "..\Header\ImagePriorty.h"

ImagePriorty::ImagePriorty(ImageDependencyListTypes imageDataS): m_ImageDataS(imageDataS)
{
}

std::shared_ptr<IImage> ImagePriorty::GetMainImage() const
{
	std::vector<std::shared_ptr<IImage>> ctImages;
	std::vector<std::shared_ptr<IImage>> mriImages;
	for (auto imageDepItr : m_ImageDataS)
	{
		auto image = imageDepItr->GetImage();
		if (!image)
			continue;
		if (image->GetImageModality() == CT)
			ctImages.push_back(image);
		else if (image->GetImageModality() == MRI)
			mriImages.push_back(image);
	}
	if (!ctImages.empty())
		return ctImages[0];
	if (!mriImages.empty())
		return mriImages[0];
	if (!m_ImageDataS.empty())
		return m_ImageDataS[0]->GetImage();
	return {};
}

std::shared_ptr<IImage> ImagePriorty::GetSecondImage() const
{
	auto mainImag = GetMainImage();
	auto found = std::find_if(m_ImageDataS.cbegin(), m_ImageDataS.cend(), [&mainImag](auto image)
	{
		return static_cast<bool>(image->GetImage()->GetUID() != mainImag->GetUID());
	});
	if (found != m_ImageDataS.end())
		return (*found)->GetImage();
	return {};
}

bool ImagePriorty::GetMainImageVisibility() const
{
	auto mainImage = GetMainImage();
	if (!mainImage)
		return{};
	const auto found = std::find_if(m_ImageDataS.cbegin(), m_ImageDataS.cend(), [&mainImage](auto image)
	{
		return static_cast<bool>(image->GetImage()->GetUID() == mainImage->GetUID());
	});
	if (found != m_ImageDataS.end())
		return (*found)->GetVisibility();

	return false;
}

bool ImagePriorty::GetSecondImageVisibility() const
{
	auto second = GetSecondImage();
	if (!second)
		return{};
	const auto found = std::find_if(m_ImageDataS.cbegin(), m_ImageDataS.cend(), [&second](auto image)
	{
		return static_cast<bool>(image->GetImage()->GetUID() == second->GetUID());
	});
	if (found != m_ImageDataS.end())
		return (*found)->GetVisibility();

	return false;
}
