#pragma once
#include "BusinessEntities\Point.h"
#include "VisualizationGeneralTypes.h"
#include "misViewerTypeDirection.h"

namespace parcast
{
	class ILandmarkLablePositionCalculator
	{
	public:
		virtual ~ILandmarkLablePositionCalculator() = default;
		virtual PointD3 GetLabelPosition(PointD3 const& landmarkPosition, misViewerTypeDirection typeDirection) const = 0;
	};
}
