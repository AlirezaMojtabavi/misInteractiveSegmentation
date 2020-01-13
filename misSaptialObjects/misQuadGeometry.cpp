#include "StdAfx.h"
#include "misQuadGeometry.h"

#include "misException.h"
#include "misMathUtils.h"

using namespace itk;

misQuadGeometry::misQuadGeometry(void)
	: m_IsValid(false)
{
}

misQuadGeometry::misQuadGeometry(
	const PointType &point1, const PointType &point2, const PointType &point3, const PointType &point4)
{
	PointType arrary [] = { point1, point2, point3, point4 };
	SetPoints(std::vector<PointType>(arrary, arrary + 4));
}


misQuadGeometry::~misQuadGeometry(void)
{
}

void misQuadGeometry::SetPoints( const std::vector<PointType> &points )
{
	VectorType normal;
	bool isValid = ComputeNormal(points, normal);
	if (!isValid)
	{
		m_IsValid = false;
		for (const auto& pt : points)
			std::cout << pt << ", ";
		std::cout << std::endl;
		return;
	}
	m_Points = points;
	m_Normal = normal;
	m_IsValid = true;
}

misQuadGeometry::PointType misQuadGeometry::GetCenter() const
{
	mis3DPoint<double> center(0, 0, 0);
	_ASSERT(m_Points.size() == 4);
	std::for_each(m_Points.begin(), m_Points.end(), [&](PointType  vec)
	{
		center = center + vec;
	});
	center[0] = center[0] / m_Points.size();
	center[1] = center[1] / m_Points.size();
	center[2] = center[2] / m_Points.size();
	return center;
}

misQuadGeometry::VectorType misQuadGeometry::GetNormal() const
{
	return m_Normal;
}

misQuadGeometry::PointType misQuadGeometry::GetPointWithDistanceToCenter(double distance)
{
	PointType center = GetCenter();
	VectorType normal = GetNormal();
	VectorType moveInNormalDirection;
	moveInNormalDirection[0] = normal[0] * distance;
	moveInNormalDirection[1] = normal[1] * distance;
	moveInNormalDirection[2] = normal[2] * distance;
	PointType res=center+moveInNormalDirection;
	return res;
}

bool misQuadGeometry::IsValid() const
{
	return m_IsValid;
}

const std::vector<misQuadGeometry::PointType> & misQuadGeometry::GetPoints() const
{
	return m_Points;
}

bool misQuadGeometry::ComputeNormal(const std::vector<PointType> &points, misQuadGeometry::VectorType &normal) const 
{
	const double epsilon = 1e-6;

	if (points.size() != 4)
		return false;

	VectorType vector1 = points[1] - points[0];
	VectorType vector2 = points[2] - points[1];
	VectorType vector3 = points[3] - points[2];
	VectorType vector4 = points[0] - points[3];

	// Test unique normal vector:
	VectorType normal1 = itk::CrossProduct(vector1, vector2);
	VectorType normal2 = itk::CrossProduct(vector2, vector3);
	VectorType normal3 = itk::CrossProduct(vector3, vector4);
	VectorType normal4 = itk::CrossProduct(vector4, vector1);
	normal1.Normalize();
	normal2.Normalize();
	normal3.Normalize();
	normal4.Normalize();
	if (!misMathUtils::AreCoordinatesClose(normal1, normal2, epsilon) || 
		!misMathUtils::AreCoordinatesClose(normal2, normal3, epsilon) || 
		!misMathUtils::AreCoordinatesClose(normal3, normal4, epsilon) || 
		!misMathUtils::AreCoordinatesClose(normal4, normal1, epsilon))
		return false;

	normal = normal1;
	return true;
}

void misQuadGeometry::GetBound( double* bounds ) const
{
	double xmin = m_Points[0][0], ymin = m_Points[0][1], zmin = m_Points[0][2];
	double xmax = xmin, ymax = ymin, zmax = zmin;
	for(const auto  &point : m_Points)
	{
		if (point[0] < xmin)
		{
			xmin = point[0];
		}
		if (point[1] < ymin)
		{
			ymin = point[1];
		}
		if (point[2] < zmin)
		{
			zmin = point[2];
		}
		if (point[0] > xmax)
		{
			xmax = point[0];
		}
		if (point[1] > ymax)
		{
			ymax = point[1];
		}
		if (point[2] > zmax)
		{
			zmax = point[2];
		}
	}
	bounds[0] = xmin;
	bounds[1] = xmax;
	bounds[2] = ymin;
	bounds[3] = ymax;
	bounds[4] = zmin;
	bounds[5] = zmax;
}
