#include "stdafx.h"

#include "DentalQuadrantFinder.h"

using namespace parcast;

DentalQuadrant DentalQuadrantFinder::GetQuadrant(std::shared_ptr<const IPanoramicCoordinatesConverter> coordConv,
	bool isOblique, parcast::Vector<double, 3> planDirection, DentalSurgeryType surgeryType) const
{
	if (coordConv)
	{
		double splineParam, n, z;
		coordConv->GetPanoramicCoordinates(splineParam, z, n);
		auto splineLength = coordConv->GetCurrentSplineLength();
		if (splineParam < splineLength / 2)
			return IsUpperJaw(isOblique, planDirection, surgeryType) ? DentalQuadrant::UpperRight : DentalQuadrant::LowerRight;
		return IsUpperJaw(isOblique, planDirection, surgeryType) ? DentalQuadrant::UpperLeft : DentalQuadrant::LowerLeft;
	}
	return IsUpperJaw(isOblique, planDirection, surgeryType) ? DentalQuadrant::UpperRight : DentalQuadrant::LowerRight;
}

bool DentalQuadrantFinder::IsUpperJaw(
	bool isOblique, parcast::Vector<double, 3> planDirection, DentalSurgeryType surgeryType) const
{
	if (isOblique)
		return planDirection[2] < 0;
	return surgeryType == DentalSurgeryType::MAXILLA;
}