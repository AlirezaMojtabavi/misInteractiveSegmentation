#pragma once
#include <misImage.h>
#include "ISimpleDataPackage.h"

namespace  parcast
{
	class IRemoveHeadRest
	{
	public:
		virtual ~IRemoveHeadRest() = default;
		virtual void SetNormalizedHeadRestVolumeThreshold(double normThreshold) = 0;
		virtual void SetRemoveHeadRestState() = 0;
		virtual bool ApplyRemoveHeadRest() = 0;
		virtual	void ResetHeadRest(misImageStatus& iamStatus) = 0;
		virtual void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> package) = 0;
		virtual void SeedUpdateInRemoveHeadRest() = 0;
	};

}
