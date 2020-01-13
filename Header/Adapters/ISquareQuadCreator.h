#pragma once

#include "BusinessEntities\Point.h"
#include "ViewVectors.h"

namespace parcast
{

	class ISquareQuadCreator
	{
	public:
		typedef Point<double, 3> PointType;

		virtual std::vector<PointType> Create(
			const ViewVectors& viewVectors, const PointType& centerPoint, double sideHalfLength) const = 0;
	};

}