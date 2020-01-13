#include "stdafx.h"
#include "Biopsy3dPlanCrossSectionFunction.h"

void parcast::Biopsy3DPlanCrossSectionFunction::SetBaseRadius(double r)
{
	m_Radius = r;
}

void parcast::Biopsy3DPlanCrossSectionFunction::SetPlanLength(double l)
{
}

double parcast::Biopsy3DPlanCrossSectionFunction::EvaluateRadius(double t)
{
	return m_Radius;
}

double parcast::Biopsy3DPlanCrossSectionFunction::EvaluateDerivative(double t)
{
	return 0;
}
