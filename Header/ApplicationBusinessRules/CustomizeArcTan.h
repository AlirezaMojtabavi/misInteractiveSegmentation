#pragma once
#include "ISingleVariableFunction.h"

namespace parcast
{

	//0.1951 * std::atan(0.19 * (x - 37.7)) + 0.7278
	class CustomizeArcTan : public ISingleVariableFunction
	{
	public:
		//a * std::atan(b * (x - c)) + d
		CustomizeArcTan(double a, double b, double c, double d) noexcept;

		double operator()(double x) const override;

	private:
		double m_A;
		double m_B;
		double m_C;
		double m_D;
	};

}
