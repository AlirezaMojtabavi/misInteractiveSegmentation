#pragma once

#include "ICornerProperties.h"

MOCK_BASE_CLASS(MockCornerProperties, ICornerProperties)
{
	MOCK_NON_CONST_METHOD(GetValidity, 0, bool());
	MOCK_CONST_METHOD(GetTransform, 0, vtkMatrix4x4*());
	MOCK_NON_CONST_METHOD(GetWidgetTransform, 0, vtkMatrix4x4*());
	MOCK_NON_CONST_METHOD(GetWidgetPositionWithDistance, 1, misSimplePointType(double distance));
	MOCK_NON_CONST_METHOD(GetCameraPosition, 0, misSimplePointType());
	MOCK_NON_CONST_METHOD(GetCameraFocalPoint, 0, misSimplePointType());
	MOCK_CONST_METHOD(GetCameraDistanceToPlane, 0, double());
	MOCK_CONST_METHOD(GetBounds, 0, double*());
	MOCK_NON_CONST_METHOD(GetTexturePoints, 1, std::vector<misSimplePointType>(IMAGEORIENTATION pOrientation));
	MOCK_NON_CONST_METHOD(GetPlanePoints, 1, std::vector<misSimplePointType>(IMAGEORIENTATION pOrientation));
	MOCK_NON_CONST_METHOD(GetPlaneViewUp, 0, misSimplePointType());
	MOCK_NON_CONST_METHOD(GetPlaneNormal, 0, misSimplePointType());
	MOCK_NON_CONST_METHOD(GetPlaneCenter, 0, misSimplePointType());
	MOCK_NON_CONST_METHOD(GetCurrentSliceNumber, 0, int());
	MOCK_NON_CONST_METHOD(GetMaxSliceNumber, 0, int());
	MOCK_NON_CONST_METHOD(GetCurrentSlicePosition, 0, double());
	MOCK_NON_CONST_METHOD(GetSliceSpacing, 0, double());
	MOCK_NON_CONST_METHOD(SetPositionBySliceNumber, 1, void(int newSliceNumber));
	typedef parcast::Point<double, 3> ParcastPointType;
	MOCK_NON_CONST_METHOD(GetCurrentPosition, 0, ParcastPointType());
	MOCK_NON_CONST_METHOD(GetCurrentPositionPoint, 0, PointType());
	MOCK_NON_CONST_METHOD(SetCurrentPosition, 1, void(const double* position));
	MOCK_NON_CONST_METHOD(SetMatrix, 1, void(vtkMatrix4x4* pTrans));
	MOCK_NON_CONST_METHOD(SetOrientation, 1, void(IMAGEORIENTATION pOrn));
	MOCK_NON_CONST_METHOD(SetObliqueMode, 1, void(bool val));
	MOCK_NON_CONST_METHOD(SetSightLineIntersectionPointTo, 1, void(double position[3]));
	MOCK_NON_CONST_METHOD(SetSightLineIntersectionPointToPlaneCenter, 0, void());
	MOCK_NON_CONST_METHOD(ResetSightLineIntersectionPoint, 0, void());
	MOCK_NON_CONST_METHOD(GetSightLineIntersectionPoint, 0, misSimplePointType());
	MOCK_NON_CONST_METHOD(SetImageProperties, 1, void(misTexturePropertyStruct prop));
	MOCK_NON_CONST_METHOD(Reset, 0, void(void));
	MOCK_NON_CONST_METHOD(GetImageSliceQuad, 0, misQuadGeometry());
	MOCK_NON_CONST_METHOD(ApplyOfsset, 1, void(double offset));
	MOCK_CONST_METHOD(GetImagePlaneOffset, 0, double());
	MOCK_NON_CONST_METHOD(SetImageSliceViewerZoomFactor, 1, void(double zoomFactor));
	MOCK_NON_CONST_METHOD(SetDentalSurgeryType, 1, void(DentalSurgeryType surgeryType));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 1, void(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter));
	MOCK_CONST_METHOD(GetPanoramicCoordinateConverter, 0, std::shared_ptr<const IPanoramicCoordinatesConverter>());
	MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double angle));
};
