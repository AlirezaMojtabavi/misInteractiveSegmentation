#pragma once
#include "IPlan.h"
namespace parcast
{
	class IPlanFactory
	{
	public:
		virtual std::shared_ptr<IPlan> CreateNewPlan(std::string const& parentImageUid) = 0;
		virtual ~IPlanFactory() = default;
	};
}