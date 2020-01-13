#pragma once

#include "VectorMatcher.h"

namespace parcast
{

	class ViewVectorMatcher
	{
	public:
		typedef parcast::Vector<double, 3> VectorType;

		explicit ViewVectorMatcher(const parcast::ViewVectors& viewVectors, double tolerance = 0.02)
			: m_ViewVectors(viewVectors),
			m_Tolerance(tolerance)
		{ }

		bool operator()(const parcast::ViewVectors& viewVectors) const
		{
			return IsEqual(m_ViewVectors, viewVectors, m_Tolerance);
		}

		static bool IsEqual(const parcast::ViewVectors& a, const parcast::ViewVectors& b, double tolerance = 0.02)
		{
			return VectorMatcher<VectorType, VectorType>::IsEqual(a.RightView, b.RightView, tolerance) &&
				VectorMatcher<VectorType, VectorType>::IsEqual(a.UpView, b.UpView, tolerance);
		}

	private:
		parcast::ViewVectors m_ViewVectors;
		double m_Tolerance;
	};

}
