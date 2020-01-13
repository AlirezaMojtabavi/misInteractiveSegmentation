#include "stdafx.h"
#include "misImageGeoProperties.h"

#include "misImage.h"
#include "misImageDataProperties.h"

misImageGeoProperties::misImageGeoProperties(vtkImageData* pimmage)
{
	m_pImage = pimmage;
	if (m_pImage)
	{
		m_spacing = m_pImage->GetSpacing();
		m_orgin = m_pImage->GetOrigin();
		m_extent = m_pImage->GetExtent();
	}

	misImage * pmisImage = dynamic_cast<misImage*>(m_pImage);
	if (pmisImage)
	{
		auto levWin = pmisImage->GetImageDataProperties()->GetViewingProperties().GetLevelWindow();
		m_WindowLevel.SetWindowParams(levWin.GetWindowCenter(), levWin.GetWindowWidth());
		m_Modality = pmisImage->GetImageModality();
	}
	_ASSERT(m_extent[0] != m_extent[1]);
	m_xCenter = m_orgin[0] + (m_extent[0] + m_extent[1])*0.5 * m_spacing[0];
	m_yCenter = m_orgin[1] + (m_extent[2] + m_extent[3])*0.5 * m_spacing[1];
	m_zCenter = m_orgin[2] + (m_extent[4] + m_extent[5])*0.5 * m_spacing[2];


	m_RealDimensions[0] = (m_extent[1] - m_extent[0])*m_spacing[0];
	m_RealDimensions[1] = (m_extent[3] - m_extent[2])*m_spacing[1];
	m_RealDimensions[2] = (m_extent[5] - m_extent[4])*m_spacing[2];
	m_confirmedDirection = false;
}

misImageGeoProperties::misImageGeoProperties()
{
	m_pImage = 0;
	m_extent = 0;
	m_spacing = 0;
	m_orgin = 0;
	m_DirectionTransform = 0;
	m_Modality = NoData;
	m_Orientation = UNKnownDirection;
	m_confirmedDirection = false;

}

double misImageGeoProperties::GetCurrentImagePositionInDirection(int index, IMAGEORIENTATION orientation)
{
	float imagePos = -1;

	switch (orientation)
	{
	case AXIAL:
	{
		imagePos = m_orgin[2] + m_spacing[2] * index;
		break;
	}
	case CORONAL:
	{
		imagePos = m_orgin[1] + m_spacing[1] * index;
		break;
	}
	case SAGITTAL:
	{
		imagePos = m_orgin[0] + m_spacing[0] * index;
		break;
	}
	};
	return imagePos;
}

double* misImageGeoProperties::GetPosition(int index[3])
{
	double *pos = new double[3];
	pos[0] = m_orgin[0] + index[0] * m_spacing[0];
	pos[1] = m_orgin[1] + index[1] * m_spacing[1];
	pos[2] = m_orgin[2] + index[2] * m_spacing[2];
	return pos;
}

int misImageGeoProperties::GetNoOfImagesInDirection(IMAGEORIENTATION orientation)
{
	// Set to -1 to show the error
	int imageSizeInSetDirection = -1;
	if ((0 == m_pImage) || (0 == m_extent))
	{
		imageSizeInSetDirection = -1;
		return imageSizeInSetDirection;
	}
	switch (orientation)
	{
	case AXIAL:
		imageSizeInSetDirection = m_extent[5] - m_extent[4] + 1;
		break;
	case CORONAL:
		imageSizeInSetDirection = m_extent[3] - m_extent[2] + 1;
		break;
	case SAGITTAL:
		imageSizeInSetDirection = m_extent[1] - m_extent[0] + 1;
		break;
	}
	return imageSizeInSetDirection;
}

int misImageGeoProperties::GetIndex(double pos, IMAGEORIENTATION orientation)
{
	int imageIndex = 0;
	switch (orientation)
	{
	case AXIAL:
	{
		imageIndex = (pos - m_orgin[2]) / m_spacing[2];
		break;
	}
	case CORONAL:
	{
		imageIndex = (pos - m_orgin[1]) / m_spacing[1];
		break;
	}
	case SAGITTAL:
	{
		imageIndex = (pos - m_orgin[0]) / m_spacing[0];
		break;
	}
	}
	return imageIndex;
}

int* misImageGeoProperties::GetIndexes(double* pos)
{
	auto imageIndexes = new int[3];
	imageIndexes[2] = (pos[2] - m_orgin[2]) / m_spacing[2];
	imageIndexes[1] = (pos[1] - m_orgin[1]) / m_spacing[1];
	imageIndexes[0] = (pos[0] - m_orgin[0]) / m_spacing[0];
	return imageIndexes;
}

misPlanePoint misImageGeoProperties::GetXYPlane()
{
	misPlanePoint res;
	res.m_p1[0] = 0;
	res.m_p1[1] = 0;
	res.m_p1[2] = 0;
	res.m_p2[0] = m_RealDimensions[0];
	res.m_p2[1] = 0;
	res.m_p2[2] = 0;
	res.m_p3[0] = 0;
	res.m_p3[1] = m_RealDimensions[1];
	res.m_p3[2] = 0;
	return  res;
}

misPlanePoint misImageGeoProperties::GetXZPlane()
{
	misPlanePoint res;
	//X axis					//Z  axis						   //Y  Axis
	res.m_p1[0] = 0;
	res.m_p1[2] = 0;
	res.m_p1[1] = 0;
	res.m_p2[0] = m_RealDimensions[0];
	res.m_p2[2] = 0;
	res.m_p2[1] = 0;
	res.m_p3[0] = 0;
	res.m_p3[1] = 0;
	res.m_p3[2] = m_RealDimensions[2];
	return  res;
}

misPlanePoint misImageGeoProperties::GetZYPlane()
{
	misPlanePoint res;
	res.m_p1[0] = 0;
	res.m_p1[2] = 0;
	res.m_p1[1] = 0;
	res.m_p2[0] = 0;
	res.m_p2[1] = m_RealDimensions[1];
	res.m_p2[2] = 0;
	res.m_p3[0] = 0;
	res.m_p3[1] = 0;
	res.m_p3[2] = m_RealDimensions[2];
	return  res;
}

void misImageGeoProperties::GetRange(double range[2])
{
	double tableRange[2];
	auto scalars = m_pImage->GetPointData()->GetScalars();
	int numberOfScalarComponents = scalars->GetNumberOfComponents();

	if (numberOfScalarComponents == 1)
	{
		scalars->GetRange(tableRange);
	}
	else
	{
		scalars->GetRange(tableRange, 3);
	}
	if (tableRange[0] < -2000)
		tableRange[0] = -2000;
	if (tableRange[1] > 3500)
		tableRange[1] = 3500;
	range[0] = tableRange[0];
	range[1] = tableRange[1];
}

double* misImageGeoProperties::GetRange()
{
	auto tableRange = new double[2];
	auto scalars = m_pImage->GetPointData()->GetScalars();
	int numberOfScalarComponents = scalars->GetNumberOfComponents();
	if (numberOfScalarComponents == 1)
	{
		scalars->GetRange(tableRange);
	}
	else
	{
		scalars->GetRange(tableRange, 3);
	}
	if (tableRange[0] < -2000)
		tableRange[0] = -2000;
	if (tableRange[1] > 3500)
		tableRange[1] = 3500;
	return tableRange;
}
int* misImageGeoProperties::GetExtend()
{
	return  m_extent;
}

double* misImageGeoProperties::GetOrigin()
{
	return  m_pImage->GetOrigin();
}

double* misImageGeoProperties::GetSpacing()
{
	return  m_pImage->GetSpacing();
}

void misImageGeoProperties::GetSpacing(double sapacing[3])
{
	auto dimsPointer = m_pImage->GetSpacing();
	for (int i = 0; i < 3; i++)
		sapacing[i] = dimsPointer[i];
}

void misImageGeoProperties::SetImage(vtkImageData* pimage)
{
	m_pImage = pimage;
	m_spacing = m_pImage->GetSpacing();
	m_orgin = m_pImage->GetOrigin();
	m_extent = m_pImage->GetExtent();
	m_xCenter = m_orgin[0] + (m_extent[0] + m_extent[1])*0.5 * m_spacing[0];
	m_yCenter = m_orgin[1] + (m_extent[2] + m_extent[3])*0.5 * m_spacing[1];
	m_zCenter = m_orgin[2] + (m_extent[4] + m_extent[5])*0.5 * m_spacing[2];
	m_RealDimensions[0] = (m_extent[1] - m_extent[0])*m_spacing[0];
	m_RealDimensions[1] = (m_extent[3] - m_extent[2])*m_spacing[1];
	m_RealDimensions[2] = (m_extent[5] - m_extent[4])*m_spacing[2];
}

vtkImageData* misImageGeoProperties::GetImage()
{
	return  m_pImage;
}

double* misImageGeoProperties::GetBound()
{
	double* bds = new double[6];
	double*  origin = GetOrigin();
	int*  extetd = GetExtend();
	double*  spacing = GetSpacing();
	bds[0] = origin[0] + (extetd[0] * spacing[0]);;
	bds[1] = origin[1] + (extetd[1] * spacing[0]);
	bds[2] = origin[1] + (extetd[2] * spacing[1]);;
	bds[3] = origin[1] + (extetd[3] * spacing[1]);
	bds[4] = origin[2] + (extetd[4] * spacing[2]);;
	bds[5] = origin[2] + (extetd[5] * spacing[2]);
	return  bds;
}

misWindowLevelStr misImageGeoProperties::GetWindowLevel()
{
	return m_WindowLevel;
}

misImageDataModality misImageGeoProperties::GetModality()
{
	if (m_Modality)
	{
		return m_Modality;
	}
	cout << "ERROR : THE VTKIMAGEDATA HAS NO MODALITY";
	return NoData;
}

vtkTransform* misImageGeoProperties::GetDirectionTransform()
{
	if (m_confirmedDirection)
	{
		return m_DirectionTransform;
	}
	return 0;
}

int* misImageGeoProperties::GetDimensions()
{
	auto dims = new int[3];
	m_pImage->GetDimensions(dims);
	return  dims;
}

void misImageGeoProperties::GetDimensions(int dims[3])
{
	auto dimsPointer = m_pImage->GetDimensions();
	for (int i = 0; i < 3; i++)  dims[i] = dimsPointer[i];
}

void misImageGeoProperties::SetWindowLevel(misWindowLevelStr WinLevStr)
{
	m_WindowLevel.SetWindowParams(WinLevStr.GetWindowCenter(), WinLevStr.GetWindowWidth());
}