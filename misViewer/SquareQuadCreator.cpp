#include "stdafx.h"
#include "SquareQuadCreator.h"
#include "misDebug.h"

std::vector<parcast::ISquareQuadCreator::PointType> parcast::SquareQuadCreator::Create(
	const ViewVectors& viewVector, const PointType& centerPoint, double halfLength) const
{
	auto halfWidth = viewVector.RightView * halfLength;
	auto halfHeight = viewVector.UpView * halfLength;

	return std::vector<PointType>
	{
		centerPoint + halfWidth + halfHeight,
		centerPoint - halfWidth + halfHeight,
		centerPoint - halfWidth - halfHeight,
		centerPoint + halfWidth - halfHeight
	};
}
