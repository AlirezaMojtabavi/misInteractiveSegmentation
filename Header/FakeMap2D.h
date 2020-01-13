#pragma once

#include "IMap2D.h"
#include "misDebug.h"
#include "misException.h"

template<typename T>
class DefaultPointEqualityComparer
{
public:
	DefaultPointEqualityComparer(T tolerance = static_cast<T>(1e-6)) : Tolerance(tolerance) { }

	bool IsEqual(T val1, T val2) const
	{
		return (val1 - val2) * (val1 - val2) <= Tolerance;
	}

	const T Tolerance;
};

// This is a fake class for IMap2D class. It takes expectation parameter for map and source and destination points and will return 
// the value in case of valid entry. 
template <typename T, class EqualityComparer = DefaultPointEqualityComparer<T>>
class FakeMap2D : public IMap2D<T>
{
public:
	FakeMap2D(const EqualityComparer equalityComparer = EqualityComparer())
		: Equality(equalityComparer)
	{
	}

	virtual MapPoint2D DestinationToSource( const MapPoint2D& point, const MapPoint2D& valueIfNotFound ) const override
	{
		auto expectationFound = std::find_if(m_DestinationToSourceExpList.cbegin(), m_DestinationToSourceExpList.cend(), 
			[this, &point] (const EvaluationExpDesc& expectation) -> bool
		{
			return IsPointEqual(point, expectation.m_Input);
		});

		if (expectationFound == m_DestinationToSourceExpList.cend())
		{
			std::stringstream message;
			message << "Unexpected call to SourceToDestination with: point = (" << point.x << ", " << point.y << ")" << std::endl;
			throw std::exception(message.str().c_str());
		}

		auto returnValue = expectationFound->m_ReturnValue;
		m_DestinationToSourceExpList.erase(expectationFound);
		return returnValue;
	}

	virtual MapPoint2D SourceToDestination( const MapPoint2D& point, const MapPoint2D& valueIfNotFound ) const override
	{
		auto expectationFound = std::find_if(m_SourceToDestinationExpList.cbegin(), m_SourceToDestinationExpList.cend(), 
			[this, &point] (const EvaluationExpDesc& expectation) -> bool
		{
			return IsPointEqual(point, expectation.m_Input);
		});

		if (expectationFound == m_SourceToDestinationExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to SourceToDestination with: point = (" << point.x << ", " << point.y << ")" << std::endl;
			throw std::exception(message.str().c_str());
		}

		auto returnValue = expectationFound->m_ReturnValue;
		m_SourceToDestinationExpList.erase(expectationFound);
		return returnValue;
	}

	virtual void AddMapping( const MapPoint2D &source, const MapPoint2D &destination ) override
	{
		auto expectationFound = std::find_if(m_AddMappingExpList.begin(), m_AddMappingExpList.end(), 
			[this, &source, &destination] (const AddMappingExpDesc& expectation) -> bool
		{
			return IsPointEqual(source, expectation.m_Source) && IsPointEqual(destination, expectation.m_Destination);
		});

		if (expectationFound == m_AddMappingExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to SourceToDestination with: point1 = (" << source.x << ", " << source.y << ")" << 
				", point2 = (" << destination.x << ", " << destination.y << ")" <<std::endl;
			throw std::exception(message.str().c_str());
		}

		m_AddMappingExpList.erase(expectationFound);
	}

	void ExpectAddMapping(const MapPoint2D &point1, const MapPoint2D &point2)
	{
		m_AddMappingExpList.push_back(AddMappingExpDesc(point1, point2));
	}

	void ExpectSourceToDestination(const MapPoint2D& point, const MapPoint2D& returnValue)
	{
		m_SourceToDestinationExpList.push_back(EvaluationExpDesc(point, returnValue));
	}

	void ExpectDestinationToSource(const MapPoint2D& point, const MapPoint2D& returnValue)
	{
		m_DestinationToSourceExpList.push_back(EvaluationExpDesc(point, returnValue));
	}

private:
	bool IsPointEqual(const MapPoint2D& point1, const MapPoint2D& point2) const
	{
		return Equality.IsEqual(point1.x, point2.x) && Equality.IsEqual(point1.y, point2.y);
	}

	struct EvaluationExpDesc
	{
		EvaluationExpDesc(const MapPoint2D& inputPoint, const MapPoint2D returnValue)
			: m_Input(inputPoint), m_ReturnValue(returnValue)
		{
		}

		const MapPoint2D m_Input, m_ReturnValue;
	};

	struct AddMappingExpDesc
	{
		AddMappingExpDesc(const MapPoint2D &point1, const MapPoint2D &point2)
			: m_Source(point1), m_Destination(point2)
		{
		}

		const MapPoint2D m_Source, m_Destination;
	};

	const EqualityComparer Equality;
	mutable std::list<EvaluationExpDesc> m_DestinationToSourceExpList;
	mutable std::list<EvaluationExpDesc> m_SourceToDestinationExpList;
	mutable std::list<AddMappingExpDesc> m_AddMappingExpList;
};