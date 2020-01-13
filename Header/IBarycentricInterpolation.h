#pragma once

// In this class we generate the result of a Barycentric Interpolation formula for a given triangle points and values 
// in the corner points. Here we have the interface for this procedure.
template <typename P, typename T>
class IBarycentricInterpolation
{
public:
	typedef T ValueType;
	typedef P PointType;

	// Sets the corner points of a triangle
	virtual void SetTriangle(const std::vector<PointType> &trianglePoints, const std::vector<ValueType> &trianglePointsValues) = 0;
	
	// Calculates the barycentric interpolation result for the given point using the triangle vertices set using SetTriangle
	virtual ValueType Interpolate(const PointType& point) const = 0;
};