#pragma once

#include "ChainBool.h"
#include "misScrewWidgetData.h"

namespace parcast
{

	class misScrewWidgetDataMatcher
	{
	public:
		misScrewWidgetDataMatcher(const misScrewWidgetData& data)
			: ThisData(data)
		{}

		bool operator()(const misScrewWidgetData& otherData)
		{
			return IsEqual(ThisData, otherData);
		}

		static bool IsEqual(const misScrewWidgetData& a, const misScrewWidgetData& b)
		{
			return ChainBool(std::cout, "misScrewWidgetDataMatcher").
				Add(a.GetEndPoint() == b.GetEndPoint()).
				Add(a.GetInterationType() == b.GetInterationType()).
				Add(a.GetScrewDiameter() == b.GetScrewDiameter()).
				Add(a.GetScrewUID() == b.GetScrewUID()).
				Add(a.GetSourceType() == b.GetSourceType()).
				Add(a.GetStartPoint() == b.GetStartPoint());
		}

	private:
		const misScrewWidgetData& ThisData;
	};

}
