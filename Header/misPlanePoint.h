#pragma once
typedef itk::Point<double, 3>  PointType;
struct misPlanePoint
{
	PointType  m_p1;
	PointType  m_p2;
	PointType  m_p3;
	double  m_spacing[3];
};
