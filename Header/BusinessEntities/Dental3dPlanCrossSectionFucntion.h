#pragma once
#include "I3DPlanCrossSectionFunction.h"

namespace parcast
{

	class Dental3dPlanCrossSectionFucntion : public parcast::I3DPlanCrossSectionFunction
	{
	public:
		void SetBaseRadius(double r) override;
		void SetPlanLength(double l) override;
		double EvaluateRadius(double t) override;
		double EvaluateDerivative(double t) override;

	private:
		double m_Radius;
		double m_Length;
	};

}

