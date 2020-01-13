#pragma once
#include "misMRICOloredColorMap.h"
#include "ICompeleteImageDependencies.h"
#include <IImage.h>
 

class ImagePriorty
{
public:
	typedef std::vector<std::shared_ptr<ICompeleteImageDependencies>> ImageDependencyListTypes;

	explicit ImagePriorty(ImageDependencyListTypes imageDataS);

	std::shared_ptr<IImage> GetMainImage() const;
	std::shared_ptr<IImage> GetSecondImage() const;
	bool GetMainImageVisibility() const;
	bool GetSecondImageVisibility() const;

private:
	ImageDependencyListTypes m_ImageDataS;

};

