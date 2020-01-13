#pragma once
#include "ICameraPositionCalculator.h"

namespace parcast
{
	class CameraPositionCalculator : public ICameraPositionCalculator
	{
	public:
		CameraPositionCalculator(PointD3 minBounding,
			PointD3 maxBounding, const double handleLength);
		PointD3 GetCameraPosition(PointD3 const& landmarkPosition) const override;
	private:
		const double CameraDistance;
		PointD3 m_MinBounding;
		PointD3 m_MaxBounding;
		const double PlaneOffset = 2.;

	};
}
