#pragma once

#include "misQuadMapperBase.h"
#include "BiopsyPlanSettingParam.h"
#include "misMathUtils.h"


class misPlanMapper : public vtkMapper
{
public:

	misPlanMapper(std::weak_ptr<ICornerProperties> cornerProperties, std::string shaderFileName, parcast::PlanSettingParam biopsyPlanParam, bool displayCross = true);
	~misPlanMapper();

	void SetStartPoint(parcast::Point<float, 3> point);
	void SetEndPoint(parcast::Point<float, 3> point);
	void SetRadius(double radius);
	void SetTargetRadius(double radius);
	void Render(vtkRenderer *ren, vtkActor *a) override;
	void SetColor(const tgt::vec3& color);
	void SetCurrentPoint(parcast::Point<float, 3> point);
	void SetInterSectionPoint(parcast::Point<float, 3> point);
	void SetNormalPlane(parcast::Vector<float, 3> vector);
	double* GetBounds();

	void GetBounds(double bounds[6]) final;
private:

	void SetShaderVariables(vtkRenderer *ren, vtkActor *a);
	void CreateGLSLObjects();
	virtual void BuildPlane();

	tgt::Shader* m_program;
	parcast::Point<float, 3> m_PlanStart{0.f,0.f,0.f};
	parcast::Point<float, 3> m_PlanEnd{10.f,10.f,10.f};
	parcast::Point<float, 3> m_CurrentPoint{ 0.f,0.f,0.f };
	parcast::Point<float, 3> m_InterSectionPoint{ 0.f,0.f,0.f };
	parcast::Vector<float ,3> m_NormalPlane{ 0.f,0.f,0.f };
	float m_TargetRadius = 0.0f;
	tgt::vec3 m_Color = {0, 1, 0};
	std::weak_ptr<ICornerProperties> m_CornerProperties;
	std::string m_ShaderFileName;
	parcast::PlanSettingParam planParam;
	bool m_DisplayCross = true;
};

