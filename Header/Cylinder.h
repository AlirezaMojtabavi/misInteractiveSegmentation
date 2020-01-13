#pragma once
#include "Point.h"

namespace parcast
{

	struct Cylinder
	{
		Point<double, 3> Point1;
		Point<double, 3> Point2;
		double Radius;
	};

}
