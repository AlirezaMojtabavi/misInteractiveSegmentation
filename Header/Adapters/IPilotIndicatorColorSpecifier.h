#pragma once
#include "IPlan.h"

namespace parcast
{

	class IPilotIndicatorColorSpecifier
	{
	public:
		virtual ~IPilotIndicatorColorSpecifier() = default;

		enum class IndicatorColor { Black, Gray, Yellow, Green, Red };

		virtual IndicatorColor GetColor() const = 0;
		virtual void SetPlan(std::weak_ptr<IPlan> plan) = 0;
	};

}
