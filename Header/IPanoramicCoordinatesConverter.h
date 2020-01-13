#pragma once

// The IPanoramicCoordinatesConverter provides an abstract interface for converting Points between the image coordinate system
// and a panoramic coordinate system defined using a curve. To convert a pair of panoramic coordinates to their equivalent
// image coordinates (or vice versa), you need to set up the coordinate systems by specifying the panoramic curve and resolution, 
// and the image dimensions respectively.
// The coordinates of the image coordinate system (X, Y, Z) are related to the panoramic coordinate system components (S, N, Z_p) 
// at each point as below:
// The S coordinate increases along the tangent to the spline curve with increasing spline independent parameter. 
// The Z_p component of the panoramic coordinates increases with decreasing Z image coordinate (with the same rate).
// The N coordinate increases along the normal to the curve such that increasing direction of all the coordinates (S, N, Z_p) 
// form a right-handed coordinate system, i.e., U_S x U_Z_p = U_N, where U_i is the unit vector along increasing i coordinate.
// The origin of each coordinate corresponds with the original curve defining the panoramic coordinate system.
// S, N, and Z_p are all metric coordinates, meaning they correspond to length along their respective directions.
class IPanoramicCoordinatesConverter
{
public:
	typedef itk::Vector<double, 3> VectorType;
	typedef itk::Point<double, 3> PointType;

	// Set the input as image coordinates
	virtual void SetImageCoordinates(double x, double y, double z) = 0;

	// Set the input as panoramic coordinates
	virtual void SetPanoramicCoordinates(double s, double z_p, double n) = 0;

	// Get out output of the conversion as image coordinates.
	virtual void GetImageCoordinates(double &x, double &y, double &z) const = 0;

	// Get out output of the conversion as panoramic coordinates.
	virtual void GetPanoramicCoordinates(double &s, double &z_p, double &n) const = 0;

	// Get the current working spline length for setting the width of rendering panel.
	virtual double GetCurrentSplineLength() const = 0;

	// Evaluate the position on the displaced spline by an spline parameter.
	virtual PointType EvaluateCurrentSpline(double s) const = 0;

	// Get the unit vector normal to the surface created by extending the curve along the Z axis. It is the cross product of 
	// curve tangential unit vector and the negative of the Z axis unit vector.
	virtual VectorType GetCurrentNormalVector() const = 0;
	virtual VectorType GetCurrentTangentialVector() const = 0;

	virtual ~IPanoramicCoordinatesConverter(void) { }
};