#pragma once
#include "IRangeMapper.h"

namespace parcast
{

	class RangeMapperException : public std::exception
	{

	public:
		RangeMapperException(const std::string& message);
		const char* what() const noexcept override;

	private:
		std::string m_Message;

	};

	class RangeMapper : public IRangeMapper
	{

	public:
		RangeMapper(
			const std::pair<double, double>& fromRange,
			const std::pair<double, double>& toRange);

		double Map(double value) const final;

	private:
		std::pair<double, double> m_FromRange;
		std::pair<double, double> m_ToRange;

	};

}