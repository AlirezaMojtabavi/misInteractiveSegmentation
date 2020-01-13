#pragma once

#include "FloatingPointCompare.h"

class PlaneAndBoxConfigurationMatcher
{
public:
	PlaneAndBoxConfigurationMatcher(const misPlaneAndBoxConfiguration& value)
		: m_Value(value)
	{ }

	bool operator()(const misPlaneAndBoxConfiguration& other)
	{
		return IsEqual(other, m_Value);
	}

	static bool IsEqual(const misPlaneAndBoxConfiguration& a, const misPlaneAndBoxConfiguration& b)
	{
		misPlaneAndBoxConfiguration::PointType boundPoint1, boundPoint2, otherBoundPoint1, otherBoundPoint2;
		a.GetBoxBounds(boundPoint1, boundPoint2);
		b.GetBoxBounds(otherBoundPoint1, otherBoundPoint2);
		bool boundsClose(
			(FloatingPointCompare::AreCoordinatesClose(boundPoint1, otherBoundPoint1) &&
				FloatingPointCompare::AreCoordinatesClose(boundPoint2, otherBoundPoint2))
			||
			(FloatingPointCompare::AreCoordinatesClose(boundPoint1, otherBoundPoint2) &&
				FloatingPointCompare::AreCoordinatesClose(boundPoint2, otherBoundPoint1)));
		return
			boundsClose &&
			FloatingPointCompare::AreCoordinatesClose(a.GetPlanePoint(), b.GetPlanePoint()) &&
			FloatingPointCompare::IsClose(a.GetPlaneOffset(), b.GetPlaneOffset());
	}
private:
	misPlaneAndBoxConfiguration m_Value;
};

