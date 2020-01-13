#pragma once

#include "BusinessEntities/Point.h"
#include "VectorMatcher.h"

namespace parcast
{

	class QuadMatcher
	{
	public:
		typedef Point<double, 3> PointType;

		QuadMatcher(const std::vector<PointType>& quad, double tolerance = 0.1)
			: m_Quad(quad), m_Tolerance(tolerance)
		{ }

		bool operator()(const std::vector<PointType>& quad)
		{
			return IsEqual(m_Quad, quad, m_Tolerance);
		}

		static bool IsEqual(const std::vector<PointType>& quad1, const std::vector<PointType>& quad2, double tolerance = 0.1)
		{
			int indexDiff = -1;
			for (int i = 0; i < 4; ++i)
				if (VectorMatcher<PointType, PointType>::IsEqual(quad1[i], quad2[0], tolerance))
					indexDiff = i;
			
			if (indexDiff == -1)
				return false;
			
			for (int i = 1; i < 4; ++i)
				if (!VectorMatcher<PointType, PointType>::IsEqual(quad1[(indexDiff + i) % 4], quad2[i], tolerance))
					return false;

			return true;
		}

	private:
		std::vector<PointType> m_Quad;
		double m_Tolerance;
	};

}
