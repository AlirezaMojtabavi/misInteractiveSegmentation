#pragma once

// The ITimeValidator class template is the abstract interface used by value wrappers that may encapsulate values that are valid
// only for a limited period of time (have a limited lifetime).
template <typename T>
class ITimedValidator
{
public:
	typedef boost::chrono::high_resolution_clock ClockType;
	typedef ClockType::time_point TimePointType;
	typedef boost::chrono::duration< double, boost::ratio<1, 1> > DoubleSecondsType;
	typename T ValueType;

	// Retrieve a reference to the encapsulated value. Make sure that the value is valid before use. Use this value with discretion
	// if it is invalid. The value is not altered when the lifetime is expired. See IsValid
	virtual const T& Value() const = 0;
	virtual T& Value() = 0;

	// Determines whether the encapsulated value is still valid (not expired).
	virtual bool IsValid() const = 0;

	// Determines whether the encapsulated value has a limited lifetime. If it is not limited, IsValid will be true at all times.
	virtual bool IsTimed() const = 0;

	// Gets the amount of time, in seconds, remaining from the lifetime of the encapsulated value. If the value is not timed, the 
	// lifetime value is undefined. Its value must be equal to the difference of current time and GetCreationTime.
	virtual double RemainingLifeTime() const = 0;

	// Gets the creation time of the validator. It's value must not be altered after the lifetime is expired.
	virtual TimePointType GetCreationTime() const = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& outStr, const ITimedValidator<T>& timedValidator)
{
	return outStr << "TimedValidator{ IsTimed{ " << timedValidator.IsTimed() << " }, IsValid{ " << timedValidator.IsValid() <<
		" }, RemainingLifeTime{ " << timedValidator.RemainingLifeTime() << " }, Value { " << timedValidator.Value() << " } }";
}