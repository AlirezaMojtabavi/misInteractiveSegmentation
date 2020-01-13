#pragma once

#include "mis3DPoint.h"

//the misQuadGeometry class provides a definition of quadrilateral in the 3D space using its 4 vertices. It then computes its 
// center point, normal vector (right handed with regard to initial point order, and a point with a specified distance from the 
// center in the normal direction.
class misQuadGeometry
{
public:
	typedef itk::Point<double, 3>  PointType;
	typedef itk::Vector<double, 3> VectorType;

	misQuadGeometry(void);

	misQuadGeometry(const PointType &point1, const PointType &point2, const PointType &point3, const PointType &point4);

	~misQuadGeometry(void);

	// Gets the center point of the quad where its diagonals should intersect.
	PointType GetCenter() const ;

	// Gets the unit normal vector of the quad based on the order of the points (right-handed).
	VectorType GetNormal() const;

	// Sets/gets the points to be used as quad vertices. The order of the points determine quad normal direction (right-handed).
	void SetPoints(const std::vector<PointType> &points);
	const std::vector<PointType> &GetPoints() const;
	
	//return position with specified distance to quad center in normal direction of plane
	PointType GetPointWithDistanceToCenter(double distance);

	// Check the number of point (4), adjacent edges being perpendicular and yielding a unique surface normal.
	bool IsValid() const;

	// Gets the bounds of the axis aligned bounding box enclosing the quad.
	void GetBound(double* bounds) const;

private:
	// Computes the surface normal of the quad created using the specified points (in the specified order) and returns true if
	// the points (in the given order) form a valid quad and false otherwise.
	bool ComputeNormal(const std::vector<PointType> &points, misQuadGeometry::VectorType &normal) const;

	std::vector<PointType> m_Points;	// See SetPoints().
	VectorType m_Normal;	// Normal vector of the quad. See ComputeNormal(), GetNormal()
	bool m_IsValid;	// Denotes whether the object contains points forming a valid quad. See ComputeNormal(), IsValid()
};

