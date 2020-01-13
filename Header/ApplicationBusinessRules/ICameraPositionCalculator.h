#pragma once
#include "BusinessEntities\Point.h"
#include "misViewerTypeDirection.h"

namespace parcast
{
	class ICameraPositionCalculator
	{
	public:
		virtual ~ICameraPositionCalculator() = default;
		virtual PointD3 GetCameraPosition(PointD3 const& landmarkPosition) const = 0;
	};
}