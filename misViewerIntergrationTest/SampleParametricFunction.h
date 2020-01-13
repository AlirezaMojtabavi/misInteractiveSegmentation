#pragma once
#include "vtkParametricFunction.h"
#include "vtkObjectFactory.h"
#include "vtkMath.h"
#include "vtkCommonComputationalGeometryModule.h" // For export macro


class VTKCOMMONCOMPUTATIONALGEOMETRY_EXPORT SampleParametricFunction :	public vtkParametricFunction
{
public:
	vtkTypeMacro(SampleParametricFunction, vtkParametricFunction);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	static SampleParametricFunction *New();
	int GetDimension() override { return 2; }
	vtkSetMacro(Radius, double);
	vtkGetMacro(Radius, double);

	void Evaluate(double uvw[3], double Pt[3], double Duvw[9]) override;
	double EvaluateScalar(double uvw[3], double Pt[3],
		double Duvw[9]) override;

private:
	SampleParametricFunction();
	~SampleParametricFunction() override;

	// Variables
	double Radius;

	SampleParametricFunction(const SampleParametricFunction&) = delete;
	void operator=(const SampleParametricFunction&) = delete;

};

vtkStandardNewMacro(SampleParametricFunction);


//----------------------------------------------------------------------------
SampleParametricFunction::SampleParametricFunction() :	Radius(1)
{
	// Preset triangulation parameters
	MinimumU = 0;
	MaximumU = 2 * vtkMath::Pi();
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
SampleParametricFunction::~SampleParametricFunction()
{
}


//----------------------------------------------------------------------------
void SampleParametricFunction::Evaluate(double uvw[3], double Pt[3], double Duvw[9])
{
	double u = uvw[0];
	double v = uvw[1];
	double *Du = Duvw;
	double *Dv = Duvw + 3;

	for (int i = 0; i < 3; ++i)
	{
		Pt[i] = Du[i] = Dv[i] = 0;
	}

	auto planRadiousFunction = [this](double v)
	{
		auto rad = (Radius * pow(MaximumV - v, 1. / 8.)) + sin(30. * v) / 30.;
		return (rad < Radius / 5. ) ? 0.0 : rad;
	};
	auto planRadiousDerivative = [this](double v)
	{
		if (v > MaximumV * .95 )
			return -1.;
		return cos(30. * v) / 30.;
	};

	// The point
	Pt[0] = planRadiousFunction(v) * cos(u);
	Pt[1] = planRadiousFunction(v) * sin(u);
	Pt[2] = v;

	//The derivatives are:
	Du[0] = -this->Radius * sin(u);
	Du[1] = this->Radius * cos(u);
	Du[2] = 0;

	Dv[0] = planRadiousDerivative(v) * cos(u);
	Dv[1] = planRadiousDerivative(v) * sin(u);
	Dv[2] = 1.0;

}

//----------------------------------------------------------------------------
double SampleParametricFunction::EvaluateScalar(double*, double*, double*)
{
	return 0;
}

//----------------------------------------------------------------------------
void SampleParametricFunction::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
	os << indent << "X scale factor: " << this->Radius << "\n";
}
