#include "stdafx.h"
#include "BusinessEntities\Point.h"
#include "CameraPositionCalculator.h"
#include "misException.h"

using namespace parcast;

CameraPositionCalculator::CameraPositionCalculator(const PointD3 minBounding,
	const PointD3 maxBounding, const double cameraDistance) :
	CameraDistance(cameraDistance), m_MinBounding(minBounding), m_MaxBounding(maxBounding)
{
	if (m_MaxBounding[0] == 0.0 && m_MaxBounding[1] == 0.0 && m_MaxBounding[2] == 0.0)
	{
		m_MaxBounding[0] = 300.;
		m_MaxBounding[1] = 300.;
		m_MaxBounding[2] = 300.;
	}
}
PointD3 CameraPositionCalculator::GetCameraPosition(PointD3 const& landmarkPosition) const
{
	const auto center = (m_MaxBounding - m_MinBounding) * .5;
	auto outwardDirection = VectorD3((landmarkPosition - center).Elements());
	outwardDirection[2] = 0.0;
	outwardDirection.Normalize();
	return landmarkPosition + outwardDirection * CameraDistance;
}
