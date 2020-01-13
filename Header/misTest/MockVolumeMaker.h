#pragma once
#include "IVolumeMaker.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVolumeMaker, IVolumeMaker)
	{
		MOCK_NON_CONST_METHOD(MakeVolumeFromImage, 3, void(std::weak_ptr<IImage> image, std::weak_ptr<ISimpleDataPackage> package, misApplicationType appType));
	};

}