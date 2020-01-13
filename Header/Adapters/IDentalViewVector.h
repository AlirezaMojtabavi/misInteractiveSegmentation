#pragma once

#include "ViewVectors.h"

namespace parcast
{
	class IDentalViewVector
	{
	public:
		virtual ~IDentalViewVector() = default;

		virtual ViewVectors CalculateMesiodistalView() const = 0;
		virtual ViewVectors CalculateOcclusalView() const = 0;
		virtual ViewVectors CalculateBuccolingualView() const = 0;
		virtual void SetViewDirections(const ViewVectors::VectorType& plan, const ViewVectors::VectorType& mesiodistal) = 0;
		virtual void SetRightViewAngularOffset(double angle) = 0;
	};
}