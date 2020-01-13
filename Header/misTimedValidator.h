#pragma once

#include "ITimedValidator.h"

// The misTimedValidator is a Concrete implementation of ITimedValidator interface that can encapsulate values that are
// copy constructible.
template <typename T>
class misTimedValidator : public ITimedValidator<T>
{
public:
	// Creates the wrapper around the given value while specifying whether it is time limited and its lifetime. The lifetime of 
	// the encapsulated value, in seconds, is counted down immediately after creating the wrapper.
	misTimedValidator(const T& newValue, bool isTimed, double lifeTime)
		: m_Value(newValue), 
		m_CreationTime(ClockType::now()), 
		m_LifeTime(lifeTime), 
		m_IsTimed(isTimed)
	{
	}

	const T& Value() const override
	{
		return m_Value;
	}

	T& Value() override
	{
		return m_Value;
	}

	bool IsValid() const override
	{
		auto diffTime = ClockType::now() - m_CreationTime;
		auto isValid = (!m_IsTimed) || (diffTime < m_LifeTime);
		return isValid;
	}

	bool IsTimed() const override
	{
		return m_IsTimed;
	}

	double RemainingLifeTime() const override
	{
		auto lifeTime = boost::chrono::duration_cast<DoubleSecondsType>(m_LifeTime - (ClockType::now() - m_CreationTime));
		return lifeTime > DoubleSecondsType::zero() ? lifeTime.count() : 0;
	}

	virtual TimePointType GetCreationTime() const
	{
		return m_CreationTime;
	}

private:	
	T m_Value;	// The encapsulated value
	ClockType::time_point m_CreationTime;	// Creation time of the wrapper
	DoubleSecondsType m_LifeTime;	// Total lifetime specified for the value
	bool m_IsTimed;	// See IsTimed()
};