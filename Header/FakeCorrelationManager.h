#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "misDebug.h"
#include "misException.h"

template <typename T>
class FakeCorrelationManager : public ICoordinateSystemCorrelationManager<T>
{
public:
	FakeCorrelationManager() { }
	
	~FakeCorrelationManager()
	{
		bool error = false;
		std::stringstream message;
		if (!m_GetTransformExpList.empty())
		{
			message << "GetTransform with Expectation(s) not satisfied:" << std::endl;
			std::for_each(m_GetTransformExpList.cbegin(), m_GetTransformExpList.cend(), 
				[this, &message] (const GetTransformExpDesc& expectation)
			{
				message << "source = " << expectation.m_Source << ", destination = " << expectation.m_Destination << "\n";
			});
		}
		if (!m_SetTransformExpList.empty())
		{
			std::stringstream message;
			message << "SetTransform with Expectation(s) not satisfied:" << std::endl;
			std::for_each(m_SetTransformExpList.cbegin(), m_SetTransformExpList.cend(), 
				[this, &message] (const SetTransformExpDesc& expectation)
			{
				message << "source = " << expectation.m_Source << ", destination = " << expectation.m_Destination << 
					", timedTransform = " << expectation.m_TimedTransform << "\n";
			});
		}
		if (error)
		{
			std::cout << message.str();
			//throw misException(message.str());
		}
	}

	virtual void SetTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination, TransformConstPtr transform)
	{
		throw std::exception("SetTransform with TransformConstPtr: The method or operation is not implemented.");
	}

	virtual void SetTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination, TimedTransformConstPtr transform)
	{
		auto expectationFound = std::find_if(m_SetTransformExpList.begin(), m_SetTransformExpList.end(), 
			[this, &source, &destination, &transform] (const SetTransformExpDesc& expectation) -> bool
		{
			return expectation.m_Source == source && expectation.m_Destination == destination && 
				expectation.m_TimedTransform == transform;
		});
		if (expectationFound == m_SetTransformExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to SetTransform with: source = " << source << 
				", destination = " << destination <<", transform = " << transform << std::endl;
			throw misException(message.str());
		}
		m_SetTransformExpList.erase(expectationFound);
	}

	virtual ComputedCorrelationConstPtr GetTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination) const
	{
		ComputedCorrelationConstPtr returnValue;
		auto expectationFound = std::find_if(m_GetTransformExpList.begin(), m_GetTransformExpList.end(), 
			[this, &source, &destination] (const GetTransformExpDesc& expectation) -> bool
		{
			return expectation.m_Source == source && expectation.m_Destination == destination;
		});
		if (expectationFound == m_GetTransformExpList.end())
		{
			std::stringstream message;
			message << "Unexpected call to GetTransform with: source = " << source << 
				", destination = " << destination << std::endl;
			throw misException(message.str());
		}
		returnValue = expectationFound->m_ReturnValue;
		m_GetTransformExpList.erase(expectationFound);
		return returnValue;
	}

	virtual void ConcatTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination, TransformConstPtr transform )
	{
		throw std::exception("ConcatTransform: The method or operation is not implemented.");
	}

	virtual void DecatTransform(const CoordinateSystemType& source, const CoordinateSystemType& destination )
	{
		throw std::exception("DecatTransform: The method or operation is not implemented.");
	}

	virtual std::list<DirectCorrelation> GetDirectCorrelationsList() const
	{
		throw std::exception("GetDirectCorrelationsList: The method or operation is not implemented.");
	}

	virtual void SetDirectCorrelationsList( const std::list<DirectCorrelation>& newList )
	{
		throw std::exception("GetDirectCorrelationsList: The method or operation is not implemented.");
	}

	void ExpectGetTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination, ComputedCorrelationConstPtr returnValue)
	{
		m_GetTransformExpList.push_back(GetTransformExpDesc(source, destination, returnValue));
	}

	void ExpectSetTransform(
		const CoordinateSystemType& source, const CoordinateSystemType& destination, TimedTransformConstPtr trans)
	{
		m_SetTransformExpList.push_back(SetTransformExpDesc(source, destination, trans));
	}

	virtual void RemoveTransform( const CoordinateSystemType & source, const CoordinateSystemType &destination )
	{
		throw std::exception("RemoveTransform: The method or operation is not implemented.");
	}

	virtual void PurgeInvalidCorrelations()
	{
		throw std::exception("PurgeInvalidCorrelations: The method or operation is not implemented.");
	}

private:
	struct GetTransformExpDesc
	{
		GetTransformExpDesc(
			const CoordinateSystemType& source, const CoordinateSystemType& destination, ComputedCorrelationConstPtr returnValue)
			: m_Source(source), m_Destination(destination), m_ReturnValue(returnValue) 
		{
		}

		const CoordinateSystemType m_Source;
		const CoordinateSystemType m_Destination;
		const ComputedCorrelationConstPtr m_ReturnValue;
	};

	struct SetTransformExpDesc
	{
		SetTransformExpDesc(
			const CoordinateSystemType& source, const CoordinateSystemType& destination, TimedTransformConstPtr trans)
			: m_Source(source), m_Destination(destination), m_TimedTransform(trans) 
		{
		}

		const CoordinateSystemType m_Source;
		const CoordinateSystemType m_Destination;
		const TimedTransformConstPtr m_TimedTransform;
	};

	mutable std::list<GetTransformExpDesc> m_GetTransformExpList;
	mutable std::list<SetTransformExpDesc> m_SetTransformExpList;
};