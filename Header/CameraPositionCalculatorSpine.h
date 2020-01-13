#pragma once
#include "ICameraPositionCalculator.h"

namespace parcast
{
	class CameraPositionCalculatorSpine : public ICameraPositionCalculator
	{
	public:
		CameraPositionCalculatorSpine(double cameraDistance);
		PointD3 GetCameraPosition(PointD3 const& landmarkPosition) const override;
	private:
		const double CameraDistance;

	};
}