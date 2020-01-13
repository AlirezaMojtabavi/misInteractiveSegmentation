#pragma once
#include "IImage.h"
#include "ISimpleDataPackage.h"

namespace parcast
{

	class IVolumeMaker
	{
	public:
		virtual ~IVolumeMaker() = default;
		virtual void MakeVolumeFromImage(std::weak_ptr<IImage> image, std::weak_ptr<ISimpleDataPackage> package,  misApplicationType appType) = 0;
	};

}
