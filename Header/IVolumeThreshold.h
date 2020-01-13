#pragma once
#include <misEnums.h>
#include "ISimpleDataPackage.h"
namespace parcast
{
	class IVolumeThreshold
	{
	public:
		virtual ~IVolumeThreshold() = default;
		virtual void SetVolumeThreshold(std::shared_ptr<ISimpleDataPackage> workingPackage, double threshold, misApplicationType appType, const misVisualizationSetting& visulaizationSetting) = 0;

	};
}
