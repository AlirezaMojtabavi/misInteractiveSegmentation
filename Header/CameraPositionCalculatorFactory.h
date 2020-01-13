#pragma once
#include "ICameraPositionCalculator.h"
#include "misEnums.h"

namespace parcast
{
	class CameraPositionCalculatorFactory : public ICameraPositionCalculator
	{
	public:
		static std::shared_ptr <ICameraPositionCalculator> Create(PointD3 minBounding,
			PointD3 maxBounding, const double handleLength, misApplicationType type);
	};
}