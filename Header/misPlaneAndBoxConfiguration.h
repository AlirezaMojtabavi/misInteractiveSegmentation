#pragma once

#include "misMacros.h"

// The misPlaneAndBoxConfiguration serves as a container for the configuration partially defining a plane and a box in space. 
// This structure can be used as part of input to classes that serve to compute intersection points of the plane and each of the 
// parallel sets of 4 edges of the box cuboid. These classes will however additionally need a normal vector which in combination 
// with the plane point defines a unique plane in space.
class misPlaneAndBoxConfiguration
{
public:
	typedef itk::Point<double, 3> PointType;	// Type used for representing spatial points
	
	// Copy constructor to initialize the object from another or copy the object to another one.
	misPlaneAndBoxConfiguration (const misPlaneAndBoxConfiguration &planeAndBoxConfiguration);	
	misPlaneAndBoxConfiguration ();	

	// Sets/gets a point on the plane of intersection as a definitive component of the plane. See also SetPlaneOffset().
	misPrivateVariableWithPublicAccessorsMacro(PointType, m_PlanePoint, PlanePoint);

	// Sets/gets the offset (zero by default) that can be used to move the effective plane point by the given distance from the 
	// defined plane point along the plane vector. See also SetPlanePoint()
	misPrivateVariableWithPublicAccessorsMacro(double, m_PlaneOffset, PlaneOffset);

	// Sets/gets the bounds of the box that supposedly contains the 3D image through Cartesian coordinates of two non-adjacent 
	// vertices of the box cuboid.
	void SetBoxBounds( const PointType &vertex1, const PointType &vertex2 );
	void GetBoxBounds(PointType& vertex1, PointType& vertex2) const;

	// Creates a point of type PointType given its Cartesian coordinates
	static PointType MakePoint(double x, double y, double z)
	{
		double coords[] = { x, y, z };
		return PointType(coords);
	}

private:
	PointType m_Point1OfBoxBounds;	// One of the box (which supposedly contains the 3D image) corners that helps us to find out box bounds.
	PointType m_Ponit2OfBoxBounds;	// One of the box (which supposedly contains the 3D image) corners that helps us to find out box bounds.
};

