#pragma once
#include "Point.h"

namespace parcast
{

	class InvalidArray : public std::exception
	{
	public:
		const char* what() const override
		{
			return "The array is not a valid transform";
		}
	};

	class Transform
	{
	public:
		Transform(const double transformArray[16])
		{
			constexpr double lastRowValid[4] = { 0., 0., 0., 1. };
			if(!std::equal(lastRowValid, lastRowValid + 4, transformArray + 12))
			{
				throw InvalidArray();
			}
			std::copy(transformArray, transformArray + 16, m_Matrix);
		}

		PointD3 TransformPoint(const PointD3& point) const
		{
			PointD3 result;
			for(int row = 0; row < 3; ++row)
			{
				const auto rowBegin = m_Matrix + row * 4;
				result[row] = std::inner_product(rowBegin, rowBegin + 3, point.Elements(), rowBegin[3]);
			}
			return result;
		}


	private:
		double m_Matrix[16];
	};

}