#include "stdafx.h"
#include "BusinessEntities\Point.h"
#include "CameraPositionCalculatorSpine.h"
#include "misException.h"

using namespace parcast;

CameraPositionCalculatorSpine::CameraPositionCalculatorSpine(double cameraDistance) :
	CameraDistance(cameraDistance)
{
 
}
PointD3 CameraPositionCalculatorSpine::GetCameraPosition(PointD3 const& landmarkPosition) const
{
	auto outwardDirection = parcast::VectorD3(0.0, -1.0, 0.0);
	outwardDirection.Normalize();
	return landmarkPosition + outwardDirection * CameraDistance;
}
