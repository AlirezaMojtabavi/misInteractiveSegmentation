#pragma once
#include "misImageToTextureMap.h"

class SegmentationTransferFunction
{
public:
	SegmentationTransferFunction(std::shared_ptr<IImage> image);
	std::shared_ptr<TransFuncIntensity> GetTransferFunction();
private:
	std::shared_ptr<IImage> m_Image;
	std::shared_ptr<TransFuncIntensity> m_TransFuncIntensity;
};

