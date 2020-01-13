#pragma once

template <typename CST>
class ICoordinateSystemCorrelationManager;

namespace parcast
{
	class IBiopsyToolTransformCalculatorNav
	{
	public:
		virtual ~IBiopsyToolTransformCalculatorNav() = default;
		virtual void SetImageUid(const std::string& uid) = 0;
	};
}
