#pragma once

#include "ITimedValidator.h"

// The FakeTimedValidator class template provides a simplistic fake implementation of the ITimedValidator interface template.
template <typename T>
class FakeTimedValidator : public ITimedValidator<T>
{
public:
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
		return m_IsValid;
	}

	bool IsTimed() const override
	{
		return m_IsTimed;
	}

	double RemainingLifeTime() const override
	{
		return m_LifeTimeRemaining;
	}

	virtual TimePointType GetCreationTime() const
	{
		return m_CreationTime;
	}

	void FakeSetIsValid(bool isValid)
	{
		m_IsValid = isValid;
	}

	void FakeSetIsTimed(bool isTimed)
	{
		m_IsTimed = isTimed;
	}

	void FakeSetRemainingLifeTime(double lifeTime)
	{
		m_LifeTimeRemaining = lifeTime;
	}

	void FakeSetCreationTime(const TimePointType &creationTime)
	{
		m_CreationTime = creationTime;
	}

	void FakeReinitialize(const T& value, bool isValid, bool isTimed, double lifeTime)
	{
		m_Value = value;
		m_IsValid = isValid;
		m_IsTimed = isTimed;
		m_LifeTimeRemaining = lifeTime;
	}

private:
	T m_Value;
	bool m_IsTimed;
	bool m_IsValid;
	double m_LifeTimeRemaining;
	TimePointType m_CreationTime;
};
