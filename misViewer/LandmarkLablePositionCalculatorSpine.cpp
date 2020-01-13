#include "stdafx.h"
#include "LandmarkLablePositionCalculatorSpine.h"
#include "BusinessEntities\Point.h"
#define PI 3.1415
 


parcast::LandmarkLablePositionCalculatorSpine::LandmarkLablePositionCalculatorSpine(const PointD3& minBounding,
	const PointD3& maxBounding, const double handleLength, const double offsetAngle) :
	HandleLength(handleLength), MinBounding(minBounding), MaxBounding(maxBounding), OffsetAngle(offsetAngle)
{
}

parcast::PointD3 parcast::LandmarkLablePositionCalculatorSpine::GetLabelPosition(PointD3 const& landmarkPosition,
	misViewerTypeDirection typeDirection) const
{
	const auto center = (MaxBounding - MinBounding) * .5;
	auto outwardVec = VectorD3((landmarkPosition - center).Elements());
	VectorD3 offset(0.0, 0.0, 0.0);
	switch (typeDirection)
	{
	case AxialDirection:
		outwardVec[2] = 0.0;
		offset[2] = PlaneOffset;
		break;
	case CoronalDirection:
		outwardVec[1] = 0.0;
		offset[1] = PlaneOffset;
		break;
	case SagittalDirection:
		outwardVec[0] = 0.0;
		offset[0] = -PlaneOffset;
		break;
	case Viewer3DLandmark:
		outwardVec = parcast::VectorD3(-0.5, -3.0, -0.5);
		break;
	}
	outwardVec.Normalize();
	return landmarkPosition + outwardVec * HandleLength + offset;
}
