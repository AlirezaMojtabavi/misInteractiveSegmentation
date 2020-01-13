#include "stdafx.h"
#include "BusinessEntities\Point.h"
#include "LandmarkLablePositionCalculator.h"
#define PI 3.1415
using namespace parcast;

LandmarkLablePositionCalculator::LandmarkLablePositionCalculator(const PointD3& minBounding,
	const PointD3& maxBounding, const double handleLength,const double offsetAngle) :
	HandleLength(handleLength), MinBounding(minBounding), MaxBounding(maxBounding), OffsetAngle(offsetAngle)
{
}

PointD3 LandmarkLablePositionCalculator::GetLabelPosition(PointD3 const& landmarkPosition,
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
		auto projInXyPlane = VectorD3(outwardVec[0], outwardVec[1], 0.0);
		auto const distFromZAxis = projInXyPlane.Length();
		const auto tanOffsetAngle = std::tan((OffsetAngle*PI) / 180.);
		outwardVec[2] = -distFromZAxis * tanOffsetAngle;
		break;
	}
	outwardVec.Normalize();
	return landmarkPosition + outwardVec * HandleLength + offset;
}
