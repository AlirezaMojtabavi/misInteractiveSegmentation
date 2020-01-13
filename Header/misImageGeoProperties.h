#pragma once

#include "VisualizationGeneralTypes.h"
#include "misImageModalityEnum.h"
#include "misWindowLevelStr.h"
#include "IImageGeoProperties.h"
#include "misPlanePoint.h"

class vtkImageData;
typedef itk::Point<double, 3>  PointType;
 

class misImageGeoProperties : public  IImageGeoProperties 
{
public:
	misImageGeoProperties(vtkImageData* pimmage);
	misImageGeoProperties();

	int	 GetIndex(double pos, IMAGEORIENTATION orientation) override;
	int	 GetNoOfImagesInDirection(IMAGEORIENTATION orientation) override;
	int* GetIndexes(double* pos) override;
	int* GetExtend() override;
	double GetCurrentImagePositionInDirection(int index, IMAGEORIENTATION orientation) override;
	misWindowLevelStr	GetWindowLevel() override;
	void SetWindowLevel(misWindowLevelStr WinLevStr) override;
	double*	GetPosition(int index[3]) override;
	double*	GetRange() override;
	double*	GetOrigin() override;
	double*	GetSpacing() override;
	void GetSpacing(double  sapacing[3]) override;
	int* GetDimensions() override;
	void GetDimensions(int dims[3]) override;
	double*	GetBound() override;
	misPlanePoint	GetXYPlane() override;
	misPlanePoint	GetXZPlane()override;
	misPlanePoint	GetZYPlane()override;
	vtkImageData*	GetImage()override;
	void SetImage(vtkImageData* pimage) override;
	void GetRange(double  range[2])override;
	misImageDataModality	GetModality() override;
	vtkTransform* GetDirectionTransform() override;

private:

	vtkImageData*			m_pImage;
	int*					m_extent;
	int						m_RealDimensions[3];
	double*					m_spacing;
	double*					m_orgin;
	double					m_xCenter, m_yCenter, m_zCenter;
	misWindowLevelStr		m_WindowLevel;
	IMAGEORIENTATION		m_Orientation;
	misImageDataModality	m_Modality;
	bool					m_confirmedDirection;
	vtkTransform*			m_DirectionTransform;
};
