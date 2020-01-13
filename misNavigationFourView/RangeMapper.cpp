#include "stdafx.h"

#include "RangeMapper.h"

using namespace parcast;

RangeMapperException::RangeMapperException(const std::string & message):
	m_Message(message)
{
}

const char * parcast::RangeMapperException::what() const noexcept
{
	return m_Message.c_str();
}

RangeMapper::RangeMapper(
	const std::pair<double, double>& fromRange, 
	const std::pair<double, double>& toRange)
{
	if (fromRange.second < fromRange.first)
	{
		throw RangeMapperException(
			"fromRange is not valid, then lower bound value must be less than upper value");
	}

	if (toRange.second < toRange.first)
	{
		throw RangeMapperException(
			"toRange is not valid, then lower bound value must be less than upper value");
	}

	m_FromRange = fromRange;
	m_ToRange = toRange;
}

double RangeMapper::Map(double value) const
{
	if (value > m_FromRange.second || value < m_FromRange.first)
	{
		throw RangeMapperException(
			"The value is not in range");
	}

	const auto normalizedValue = value / (m_FromRange.second - m_FromRange.first);
	return (normalizedValue * (m_ToRange.second - m_ToRange.first)) + m_ToRange.first;
}
