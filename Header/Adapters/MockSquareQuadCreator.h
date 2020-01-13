#pragma once

#include "ISquareQuadCreator.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSquareQuadCreator, ISquareQuadCreator)
	{
		MOCK_CONST_METHOD(Create, 3, std::vector<parcast::ISquareQuadCreator::PointType>(
			const parcast::ViewVectors& viewVector, const parcast::ISquareQuadCreator::PointType& centerPoint, double sideLength));
	};

}

