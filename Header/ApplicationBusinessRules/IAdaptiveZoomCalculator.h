#pragma once

namespace parcast
{

	class IAdaptiveZoomCalculator
	{
	public:
		virtual ~IAdaptiveZoomCalculator() = default;

		virtual double GetZoomFactor() const = 0;
	};

}