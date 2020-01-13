#pragma once
#include "CorrelationData.h"
#include "CompareCollections.h"

namespace parcast
{
	class CorrelationDataListMatcher
	{
	public:
		CorrelationDataListMatcher(const std::vector<CorrelationData>& correlationData) : m_CorrelationData(correlationData)
		{
		}

		static bool IsEqual(const std::vector<CorrelationData>& listA, const std::vector<CorrelationData>& listB)
		{
			auto result = CompareUnorderedCollections(listA, listB, Are2CorrelationDataEqual);
			return result;
		}

		static bool Are2CorrelationDataEqual(const CorrelationData& a, const CorrelationData& b)
		{
			auto result = true;
			result &= a.SolutionUid == b.SolutionUid;
			result &= a.DestinationUid == b.DestinationUid;
			result &= a.SourceUid == b.SourceUid;
			result &= a.Transform == b.Transform;
			return result;
		}

		bool operator()(const std::vector<CorrelationData>& other) const
		{
			return IsEqual(m_CorrelationData, other);
		}

	private:
		const std::vector<CorrelationData>& m_CorrelationData;
	};
}
