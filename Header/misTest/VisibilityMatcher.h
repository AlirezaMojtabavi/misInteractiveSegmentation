#pragma once

#include "misPlaneContrast.h"

namespace parcast
{
	class VisibilityMatcher
	{

	public:

		explicit VisibilityMatcher(std::vector<std::map<misPlaneEnum, bool>> visibilityMap) :m_Visibility(visibilityMap)
		{

		}
		bool operator()(std::vector<std::map<misPlaneEnum, bool>> other) const
		{
			return AreEqual(m_Visibility, other);
		}

		static bool AreEqual(std::vector<std::map<misPlaneEnum, bool>> a, std::vector<std::map<misPlaneEnum, bool>> b)
		{
			return a.size() == b.size() &&
				std::equal(a.begin(), a.end(), b.begin());
		}
	private:
		std::vector<std::map<misPlaneEnum, bool>> m_Visibility;
	};
}
