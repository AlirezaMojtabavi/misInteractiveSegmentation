#pragma once
namespace parcast
{
	class I3DPlanCrossSectionFunction;
}
class mis3DPlanParametricFunction : public vtkParametricFunction
{
public:
	vtkTypeMacro(mis3DPlanParametricFunction, vtkParametricFunction);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	static mis3DPlanParametricFunction *New();
	int GetDimension() override { return 2; }

	void Evaluate(double uvw[3], double Pt[3], double Duvw[9]) override;
	double EvaluateScalar(double uvw[3], double Pt[3], double Duvw[9]) override;
	void SetMaximumV(double maxV) override;
	void SetCrossSectionFucntion(std::unique_ptr<parcast::I3DPlanCrossSectionFunction> function);
	void SetRadius(double r);
	double GetRadius();

private:
	mis3DPlanParametricFunction();
	mis3DPlanParametricFunction(const mis3DPlanParametricFunction&) = delete;
	void operator=(const mis3DPlanParametricFunction&) = delete;

	double m_Radius;
	std::unique_ptr<parcast::I3DPlanCrossSectionFunction> m_CrossSectionFunction;

};


