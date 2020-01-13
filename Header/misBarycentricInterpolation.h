#pragma once

#include "IBarycentricInterpolation.h"

template <typename P, typename T>
class misBarycentricInterpolation : public IBarycentricInterpolation<typename P, typename T>
{
public:
	virtual void SetTriangle(
		const std::vector<PointType> &trianglePoints, const std::vector<ValueType> &trianglePointsValues) override
	{
		m_TrianglePoints = trianglePoints;
		m_TrianglePointsValues = trianglePointsValues;
	}

	virtual ValueType Interpolate(const PointType& point) const override
	{
		auto totalArea = AreaCalculator(m_TrianglePoints[0], m_TrianglePoints[1], m_TrianglePoints[2]);

		auto firtsPointWeight = AreaCalculator(m_TrianglePoints[1], m_TrianglePoints[2], point) / totalArea;
		auto secondPointWeight = AreaCalculator(m_TrianglePoints[0], m_TrianglePoints[2], point) / totalArea;
		auto thirdPointWeight = AreaCalculator(m_TrianglePoints[0], m_TrianglePoints[1], point) / totalArea;

		ValueType result;
		result = firtsPointWeight * m_TrianglePointsValues[0] + secondPointWeight * m_TrianglePointsValues[1] + 
			thirdPointWeight * m_TrianglePointsValues[2];

		return result;
	}

private:

	// Calculates the area of the given triangle with 3 points
	ValueType AreaCalculator(const PointType& point1, const PointType& point2, const PointType& point3) const 
	{
		ValueType area = std::abs(point1.x * point2.y + point2.x * point3.y + point3.x * point1.y 
			- point1.y * point2.x - point2.y * point3.x - point3.y * point1.x) / 2;
		return area;
	}

	// Holds the triangle points
	std::vector<PointType> m_TrianglePoints;

	// Holds the values attributed to each of the triangle corner points.
	std::vector<ValueType> m_TrianglePointsValues;

};