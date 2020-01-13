#pragma once
#include "IImplantSource.h"
#include "BiopsyPlanSettingParam.h"

class misPlanMapper;
class ICornerProperties;

class mis2DImplant : public IImplantSource
{
public:
	mis2DImplant(std::string const& shaderPath, std::weak_ptr<ICornerProperties> cornerProperties, parcast::PlanSettingParam biopsyPlanParam, bool displayCross);
	~mis2DImplant();

	void SetEntry(const parcast::PointD3& point) override;
	parcast::PointD3 GetEntry() const noexcept override;
	void SetTarget(const parcast::PointD3& point) override;
	parcast::PointD3 GetTarget() const noexcept override;
	void SetRadius(double radius) override;
	double GetRadius() const noexcept override;
	void SetTargetRadius(double radius) override;
	vtkSmartPointer<vtkMapper> GetMapper() const noexcept override;
	void SetCurrentPoint(const parcast::PointD3& point) override;
	void SetInterSectionPoint(const parcast::PointD3& point) override;
	void SetNormalPlane(const parcast::VectorD3& vector) override;

private:
		
	misPlanMapper* m_PlanMapper;
	parcast::PointD3 m_StartPoint;
	parcast::PointD3 m_EndPoint;
	parcast::PointD3 m_CurrentPoint;
	parcast::PointD3 m_InterSectionPoint;
	parcast::VectorD3 m_NormalPlane;
	double m_Radius = 0.0;
	bool m_DisplayCross;
};
