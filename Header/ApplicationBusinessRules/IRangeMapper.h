#pragma once

namespace parcast
{

	class IRangeMapper
	{

	public:
		virtual ~IRangeMapper() = default;
		virtual double Map(double value) const = 0;

	};

}