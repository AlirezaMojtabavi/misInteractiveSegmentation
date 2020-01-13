#pragma once

#include "IImageGeoProperties.h"

MOCK_BASE_CLASS(MockImageGeoProperties, IImageGeoProperties)
{
	MOCK_NON_CONST_METHOD(GetIndex, 2, int(double pos, IMAGEORIENTATION orientation));
	MOCK_NON_CONST_METHOD(GetNoOfImagesInDirection, 1, int(IMAGEORIENTATION orientation));
	MOCK_NON_CONST_METHOD(GetIndexes, 1, int*(double* pos));
	MOCK_NON_CONST_METHOD(GetExtend, 0, int*());
	MOCK_NON_CONST_METHOD(GetCurrentImagePositionInDirection, 2, double(int index, IMAGEORIENTATION orientation));
	MOCK_NON_CONST_METHOD(GetWindowLevel, 0, misWindowLevelStr());
	MOCK_NON_CONST_METHOD(SetWindowLevel, 1, void(misWindowLevelStr WinLevStr));
	MOCK_NON_CONST_METHOD(GetPosition, 1, double*(int index[3]));
	MOCK_NON_CONST_METHOD(GetRange, 0, double*(), GetRange_1);
	MOCK_NON_CONST_METHOD(GetOrigin, 0, double*());
	MOCK_NON_CONST_METHOD(GetSpacing, 0, double*(), GetSpacing_1);
	MOCK_NON_CONST_METHOD(GetSpacing, 1, void(double  sapacing[3]), GetSpacing_2);
	MOCK_NON_CONST_METHOD(GetDimensions, 0, int*(), GetDimensions_1);
	MOCK_NON_CONST_METHOD(GetDimensions, 1, void(int dims[3]), GetDimensions_2);
	MOCK_NON_CONST_METHOD(GetBound, 0, double*());
	MOCK_NON_CONST_METHOD(GetXYPlane, 0, misPlanePoint());
	MOCK_NON_CONST_METHOD(GetXZPlane, 0, misPlanePoint());
	MOCK_NON_CONST_METHOD(GetZYPlane, 0, misPlanePoint());
	MOCK_NON_CONST_METHOD(GetImage, 0, vtkImageData*());
	MOCK_NON_CONST_METHOD(SetImage, 1, void(vtkImageData* pimage));
	MOCK_NON_CONST_METHOD(GetRange, 1, void(double  range[2]) , GetRange_2);
	MOCK_NON_CONST_METHOD(GetModality, 0, misImageDataModality());
	MOCK_NON_CONST_METHOD(GetDirectionTransform, 0, vtkTransform*());
};
