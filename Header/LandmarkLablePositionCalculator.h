#pragma once
#include "ILandmarkLablePositionCalculator.h"
#include "misViewerTypeDirection.h"
#include "ISettingsContainer.h"

namespace parcast
{
	class LandmarkLablePositionCalculator : public ILandmarkLablePositionCalculator
	{
	public:
		LandmarkLablePositionCalculator(const PointD3& minBounding,
			const PointD3& maxBounding, const double handleLength, const double offsetAngle);
		PointD3 GetLabelPosition(PointD3 const& landmarkPosition, misViewerTypeDirection typeDirection) const override;
	private:
		const double HandleLength;
		const PointD3 MinBounding;
		const PointD3 MaxBounding;
		const double PlaneOffset = 2.;
		const double OffsetAngle;
	};
}
