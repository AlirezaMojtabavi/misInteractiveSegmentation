#pragma once
#include <VisualizationGeneralTypes.h>
#include <misWindowLevelStr.h>
#include "misPlanePoint.h"


class IImageGeoProperties
{
public:
	virtual ~IImageGeoProperties() = default;
	virtual int	 GetIndex(double pos, IMAGEORIENTATION orientation) = 0;
	virtual int	 GetNoOfImagesInDirection(IMAGEORIENTATION orientation) = 0;
	virtual int* GetIndexes(double* pos) = 0;
	virtual int* GetExtend() = 0;
	virtual double GetCurrentImagePositionInDirection(int index, IMAGEORIENTATION orientation) = 0;
	virtual misWindowLevelStr	GetWindowLevel() = 0;
	virtual void SetWindowLevel(misWindowLevelStr WinLevStr) = 0;
	virtual double*	GetPosition(int index[3]) = 0;
	virtual double*	GetRange() = 0;
	virtual double*	GetOrigin() = 0;
	virtual double*	GetSpacing() = 0;
	virtual void GetSpacing(double  sapacing[3]) = 0;
	virtual int* GetDimensions() = 0;
	virtual void GetDimensions(int dims[3]) = 0;
	virtual double*	GetBound() = 0;
	virtual misPlanePoint	GetXYPlane() = 0;
	virtual misPlanePoint	GetXZPlane() = 0;
	virtual misPlanePoint	GetZYPlane() = 0;
	virtual vtkImageData*	GetImage() = 0;
	virtual void SetImage(vtkImageData* pimage) = 0;
	virtual void GetRange(double  range[2]) = 0;
	virtual misImageDataModality GetModality() = 0;
	virtual vtkTransform* GetDirectionTransform() = 0;
};
