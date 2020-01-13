#pragma once

#include "ISquareQuadCreator.h"

namespace parcast 
{

	class SquareQuadCreator : public ISquareQuadCreator
	{
	public:
		virtual std::vector<PointType> Create(
			const ViewVectors& viewVector, const PointType& centerPoint, double halfLength) const override;
	};
}