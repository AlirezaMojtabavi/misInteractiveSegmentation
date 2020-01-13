#pragma once
#include "ILandmarkLablePositionCalculator.h"
#include "misEnums.h"

namespace parcast
{
	class LandmarkLablePositionCalculatorFactory : public ILandmarkLablePositionCalculator
	{
	public:
		static std::shared_ptr <ILandmarkLablePositionCalculator> Create(const PointD3& minBounding,
			const PointD3& maxBounding, const double handleLength, const double offsetAngle, misApplicationType type );
	};
}