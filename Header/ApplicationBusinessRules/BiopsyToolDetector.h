#pragma once
#include "IBiopsyToolDetector.h"

namespace parcast
{

	class BiopsyToolDetector : public IBiopsyToolDetector
	{
	public:
		BiopsyToolDetector(double distance, double tolerance);
		boost::optional<std::pair<PointD3, PointD3>> Detect(const std::vector<PointD3>& points) const override;

	private:
		double m_Distance;
		double m_Tolerance;
	};

}