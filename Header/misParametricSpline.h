#pragma once

#include "IParametricSpline.h"

class misParametricSpline : public IParametricSpline
{
public:
	misParametricSpline(const std::vector<PointType>& inputPointSet, double precision = 0.1);

	// IParametricSpline interface:
	virtual PointType EvaluateAt(double splineParameter) const override;
	virtual double GetLength() const override;
	virtual double GetPartialLength(double minVal, double maxVal) const override;
	virtual double GetSplineParamByPartialLength(double length) const override;
	virtual double GetSplineParamByPartialLength(double length, double minVal) const override;
	virtual VectorType ComputeNormalVecAt(double splineParam) const override;
	virtual VectorType ComputeTangentialVecAt(double splineParam) const override;
	virtual std::shared_ptr<IParametricSpline> GetDisplacedSpline(double displacementSize) const override;
	virtual double GetMinParameter() const override;
	virtual double GetMaxParameter() const override;

private:
	// 
	const double CoarseLengthComputationStepSize;

	// Calculate the spline length between minVal and maxVal of the spline parameter. 
	double ComputeLength(double minVal, double maxVal, double stepSize) const;

	// Calculate a step size based on the spline coarse length, considering the precision and the minimum and 
	// the maximum value for the spline parameter.
	double ComputeStepSize() const;

	//
	PointType DisplacePointAlongNormal(double s, double displacementSize) const;

	vtkSmartPointer<vtkParametricSpline> m_ParametricSpline;
	double m_Precision;
	double m_CoarseLength;
	double m_StepSize;
};