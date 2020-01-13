#pragma once

#include "IBarycentricInterpolation.h"
#include "misDebug.h"
#include "misException.h"

template<typename T>
class DefaultPointEqualityComparer
{
public:
	DefaultPointEqualityComparer(T tolerance = static_cast<T>(1e-4)) : Tolerance(tolerance) { }

	bool IsEqual(T val1, T val2) const
	{
		return (val1 - val2) * (val1 - val2) <= Tolerance;
	}

	const T Tolerance;
};

// This is a fake class for IBarycentricInterpolation class. It takes expectation parameter for interpolation triangles and
// values of the corners, desired point and its value and will return the value in case of valid entry. 

template <typename P, typename T, class EqualityComparer = DefaultPointEqualityComparer<T>>
class FakeBarycentricInterpolation : public IBarycentricInterpolation<typename P, typename T>
{
public:
	FakeBarycentricInterpolation(const EqualityComparer equalityComparer = EqualityComparer())
		: Equality(equalityComparer)
	{
	}

	virtual void SetTriangle(
		const std::vector<PointType> &trianglePoints, const std::vector<ValueType> &trianglePointsValues) override
	{
		auto expectationFound = std::find_if(m_SetTriangleExpList.begin(), m_SetTriangleExpList.end(), 
			[this, &trianglePoints, &trianglePointsValues] (const SetTriangleExpDesc& expectation) -> bool
		{
			return IsPointVectorEqual(trianglePoints, expectation.m_TrianglePoints) &&
				IsValueVectorEqual(trianglePointsValues, expectation.m_TriangleValues);
		});

		if (expectationFound == m_SetTriangleExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to SetTriangle with: Triangle with points:" << std::endl;
			for (int i = 0; i < 3; ++i)
				message << "(" << trianglePoints[i].x << ", " << trianglePoints[i].y << ") -> " 
				<< trianglePointsValues[i] << std::endl;
			throw std::exception(message.str().c_str());
		}

		m_SetTriangleExpList.erase(expectationFound);
	}

	virtual ValueType Interpolate(const PointType& point) const override
	{
		auto expectationFound = std::find_if(m_InterpolateExpList.cbegin(), m_InterpolateExpList.cend(), 
			[this, &point] (const InterpolateExpDesc& expectation) -> bool
		{
			return this->IsPointEqual(point, expectation.m_Point);
		});

		if (expectationFound == m_InterpolateExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to Interpolate with: point = (" << point.x << ", " << point.y << ")" << std::endl;
			throw std::exception(message.str().c_str());
		}

		auto returnValue = expectationFound->m_Result;
		m_InterpolateExpList.erase(expectationFound);
		return returnValue;
	}

	void ExpectSetTriangle(const std::vector<PointType> &trianglePoints, const std::vector<ValueType> &trianglePointsValues)
	{
		m_SetTriangleExpList.push_back(SetTriangleExpDesc(trianglePoints, trianglePointsValues));
	}

	void ExpectInterpolate(const PointType& point, const ValueType& returnValue)
	{
		m_InterpolateExpList.push_back(InterpolateExpDesc(point, returnValue));
	}

private:
	bool IsPointEqual(const PointType& point1, const PointType& point2) const
	{
		return Equality.IsEqual(point1.x, point2.x) && Equality.IsEqual(point1.y, point2.y);
	}

	template<typename T>
	bool IsValueVectorEqual(const std::vector<T> &vector1, const std::vector<T> vector2)
	{
		int num = 0;
		for (int i = 0; i < vector1.size(); i++)
		{
			for(int j = 0; j < vector2.size(); j++)
			{
				if(Equality.IsEqual(vector1[i], vector2[j]))
				{
					num++;
					continue;
				}
			}
		}
		if(num >= vector1.size())
			return true;
		return false;
	}

	bool IsPointVectorEqual(const std::vector<PointType> &vector1, const std::vector<PointType> vector2)
	{
		int num = 0;
		for (int i = 0; i < vector1.size(); i++)
		{
			for(int j = 0; j < vector2.size(); j++)
			{
				if(IsPointEqual(vector1[i], vector2[j]))
				{
					num++;
					continue;
				}
			}
		}
		if(num == vector1.size())
			return true;
		return false;
	}

	struct SetTriangleExpDesc
	{
		SetTriangleExpDesc(const std::vector<PointType> &points, const std::vector<ValueType> &values)
			: m_TrianglePoints(points), m_TriangleValues(values)
		{
		}

		//SetTriangleExpDesc& operator= (const SetTriangleExpDesc& other)
		//{
		//	m_TrianglePoints = other.m_TrianglePoints;
		//	m_TriangleValues = other.m_TriangleValues;
		//}

		std::vector<PointType> m_TrianglePoints;
		std::vector<ValueType> m_TriangleValues;
	};

	struct InterpolateExpDesc
	{
		InterpolateExpDesc(const PointType& point, const ValueType value)
			: m_Point(point), m_Result(value)
		{
		}

		//InterpolateExpDesc& operator= (const InterpolateExpDesc& other)
		//{
		//	m_Point = other.m_Point;
		//	m_Result = other.m_Result;
		//}

		PointType m_Point;
		ValueType m_Result;
	};

	const EqualityComparer Equality;
	mutable std::vector<InterpolateExpDesc> m_InterpolateExpList;
	mutable std::vector<SetTriangleExpDesc> m_SetTriangleExpList;
};