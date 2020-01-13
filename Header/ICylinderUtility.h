#pragma once
#include "Point.h"

namespace parcast
{

	class ICylinderUtility
	{
	public:
		virtual ~ICylinderUtility() = default;

		virtual bool IsInCylinder(const Point<double, 3>& x) const = 0;
	};

}