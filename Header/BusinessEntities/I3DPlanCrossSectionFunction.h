#pragma once
namespace parcast
{
	class I3DPlanCrossSectionFunction
	{
	public:
		~I3DPlanCrossSectionFunction() = default;
		virtual void SetBaseRadius(double r) = 0;
		virtual void SetPlanLength(double l) = 0;
		virtual double EvaluateRadius(double t) = 0;
		virtual double EvaluateDerivative(double t) = 0;
	};
}
