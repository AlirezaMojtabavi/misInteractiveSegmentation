#pragma once
#include "misCompeletePlanDataDependensiesStrct.h"

namespace parcast
{
	class IPackagePlanRelFactory
	{
	public:
		virtual ~IPackagePlanRelFactory() = default;
		virtual std::shared_ptr<IPackagePlanRel> Create(const std::string& packegUid, const std::string& planUid) const = 0;
	};
}
