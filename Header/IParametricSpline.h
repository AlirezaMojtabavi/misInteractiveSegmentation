#pragma once

// This class is a wrapper for VTKParametricSpline class which have some functions for special calculations on VTK 
// spline.
class IParametricSpline
{
public:
	typedef itk::Point<double, 3> PointType;
	typedef itk::Vector<double, 3> VectorType;

	// Calculates the point coordinates for an input spline parameter. 
	virtual PointType EvaluateAt(double splineParameter) const = 0;

	// Calculates the spline length.
	virtual double GetLength() const = 0;

	// Calculates the length of a part of the curve with spline parameter from minVal to maxVal. 
	virtual double GetPartialLength(double minVal, double maxVal) const = 0;

	// Finds the spline parameter based on the input partial length. The initial spline parameter for the search 
	// is set to minVal.
	virtual double GetSplineParamByPartialLength(double length, double minVal) const = 0;

	// Finds the spline parameter based on the input partial length. The initial spline parameter for the 
	// search is set to spline minimum parameter.
	virtual double GetSplineParamByPartialLength(double length) const = 0;

	// Calculate the spline normal vector for an input spline parameter. The normal vector direction is calculated based
	// on cross product between tangent to the spline (in the direction of increasing independent parameter) and 
	// the negative z axis.
	virtual VectorType ComputeNormalVecAt(double splineParam) const = 0;

	virtual VectorType ComputeTangentialVecAt(double splineParam) const = 0;

	// Displace original spline along its normal vector at each point. 
	virtual std::shared_ptr<IParametricSpline> GetDisplacedSpline(double displacementSize) const = 0;

	// Get minimum normalized spline parameter.
	virtual double GetMinParameter() const = 0;

	// Get maximum normalized spline parameter.
	virtual double GetMaxParameter() const = 0;
};
