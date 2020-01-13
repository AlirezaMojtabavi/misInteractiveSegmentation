#include "stdafx.h"
#include "mis3DPlanParametricFunction.h"
#include "I3DPlanCrossSectionFunction.h"
vtkStandardNewMacro(mis3DPlanParametricFunction)

//----------------------------------------------------------------------------
mis3DPlanParametricFunction::mis3DPlanParametricFunction() : m_Radius(1)
{
	// Preset triangulation parameters
	MinimumU = 0;
	MaximumU = 2. * vtkMath::Pi();
	MinimumV = 0;
	MaximumV = 3;

	JoinU = 0;
	JoinV = 0;
	TwistU = 1;
	TwistV = 0;
	ClockwiseOrdering = 1;
	DerivativesAvailable = 1;
}

//----------------------------------------------------------------------------
void mis3DPlanParametricFunction::Evaluate(double uvw[3], double pt[3], double duvw[9])
{
	auto const u = uvw[0];
	auto const v = uvw[1];
	auto *du = duvw;
	auto *dv = duvw + 3;

	for (auto i = 0; i < 3; ++i)
		pt[i] = du[i] = dv[i] = 0;

	// The point
	pt[0] = m_CrossSectionFunction->EvaluateRadius(v) * cos(u);
	pt[1] = v;
	pt[2] = m_CrossSectionFunction->EvaluateRadius(v) * sin(u);

	//The derivatives are:
	du[0] = -m_CrossSectionFunction->EvaluateRadius(v) * sin(u);
	du[1] = 0;
	du[2] = m_CrossSectionFunction->EvaluateRadius(v) * cos(u);

	dv[0] = m_CrossSectionFunction->EvaluateDerivative(v) * cos(u);
	dv[1] = 1.0;
	dv[2] = m_CrossSectionFunction->EvaluateDerivative(v) * sin(u);

}

//----------------------------------------------------------------------------
double mis3DPlanParametricFunction::EvaluateScalar(double*, double*, double*)
{
	return 0;
}

void mis3DPlanParametricFunction::SetCrossSectionFucntion(std::unique_ptr<parcast::I3DPlanCrossSectionFunction> function)
{
	m_CrossSectionFunction = std::move(function);
}

void mis3DPlanParametricFunction::SetRadius(double r)
{
	m_Radius = r;
	m_CrossSectionFunction->SetBaseRadius(r);
}

double mis3DPlanParametricFunction::GetRadius()
{
	return m_Radius;
}

void mis3DPlanParametricFunction::SetMaximumV(double maxV)
{
	MaximumV = maxV;
	m_CrossSectionFunction->SetPlanLength(maxV);
}

//----------------------------------------------------------------------------
void mis3DPlanParametricFunction::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
	os << indent
		<< "Radius: " << m_Radius << "\n"
		<< "Lenght: " << MaximumV << "\n";

}

