#pragma once

#include "IPanoramicCoordinatesConverter.h"
#include "IParametricSpline.h"

class misPanoramicCoordinatesConverter : public IPanoramicCoordinatesConverter
{
public:

	class Injector
	{
	public:
		std::shared_ptr<IParametricSpline> CreateParametricSpline(
			std::vector<PointType> splinePoints, double precision ) const;
	};

	// Create and initialize the converter. The panoramic curve is specified by a set of points which be used for creating a 
	// curve spline, and image dimensions using x, y, and z.
	misPanoramicCoordinatesConverter(const std::vector<PointType>& panoramicCurvePoints, 
		double imageDimZ, double precision = 0.1, std::shared_ptr<Injector> injector = nullptr);

	// Set the S coordinate precision in conversion from image to panoramic coordinates.
	void SetPanoramicSPrecision(double precision);

	virtual void SetImageCoordinates( double x, double y, double z ) override;
	virtual void SetPanoramicCoordinates( double s, double z_p, double n ) override;
	virtual void GetImageCoordinates( double &x, double &y, double &z ) const override;
	virtual void GetPanoramicCoordinates( double &s, double &z_p, double &n ) const override;
	virtual double GetCurrentSplineLength() const override;
	virtual VectorType GetCurrentNormalVector() const override;
	virtual VectorType GetCurrentTangentialVector() const override;
	virtual PointType EvaluateCurrentSpline(double s) const override;

private:
	double FindClosestPointOnSpline(std::shared_ptr<IParametricSpline> spline, const PointType& toPoint) const;

	double MinimizeExpressionToFindSplineParam(std::shared_ptr<IParametricSpline> spline, 
		std::function<double (double sP)> expression) const;

	void MinimizeExpressionToNarrowParamRange(
		int divisions, double& start, double& end, std::function<double (double sP)> expression) const;


private:
	const int NumberOfSplineDivisionsPerSplinedPoint;
	const int NumberOfSplineDivisionsPerSubsequentPass;
	
	std::shared_ptr<IParametricSpline> m_OriginalCurveSpline;
	std::shared_ptr<IParametricSpline> m_DisplacedSpline;
	double m_Precision;
	int m_InitialNumberOfSplineDivisions;
	double m_ImageDimensionZ;
	double m_ImageX, m_ImageY, m_ImageZ;
	double m_PanoramicS, m_PanoramicN, m_PanoramicZp;
	std::shared_ptr<Injector> m_Injector;
};