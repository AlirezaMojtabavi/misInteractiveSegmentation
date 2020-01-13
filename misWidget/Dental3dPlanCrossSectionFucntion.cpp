#include "stdafx.h"
#include "Dental3dPlanCrossSectionFucntion.h"

using namespace parcast;
void Dental3dPlanCrossSectionFucntion::SetBaseRadius(double r)
{
	m_Radius = r;
}

void Dental3dPlanCrossSectionFucntion::SetPlanLength(double l)
{
	m_Length = l;
}

double Dental3dPlanCrossSectionFucntion::EvaluateRadius(double t)
{
	const auto radius = (m_Radius * pow(m_Length - t, 1. / 8.)) + sin(10. * t) * (m_Radius / 5.);
	return (radius < m_Radius / 3.) ? 0.0 : radius;
}

double Dental3dPlanCrossSectionFucntion::EvaluateDerivative(double t)
{
	if (t > m_Length* .95)
		return -1.;
	return cos(10. * t) * (m_Radius/ 5.);
}
