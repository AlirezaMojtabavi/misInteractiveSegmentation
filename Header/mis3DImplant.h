#pragma once
#include "IImplantSource.h"
#include "I3DPlanCrossSectionFunction.h"
#include "mis3DPlanParametricFunction.h"

class mis3DImplant : public IImplantSource
{

public:
	explicit mis3DImplant(std::unique_ptr<parcast::I3DPlanCrossSectionFunction> crossSectionFunction,
		bool showDirectionAxis, double lineRadius , double lineHeight );

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

	const int m_NumberofSides = 30;
	const double LineResolution = 10;
	double m_Radius = 1;
	double m_LineRadius = 0.35;
	double m_LineHeight = 200;

	void Update(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint);
	vtkSmartPointer<vtkTransform> CalculateRotationMatrix(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint);
	void RotateTranform(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint, vtkSmartPointer<vtkTransform>& transform);

	parcast::PointD3 m_StartPoint, m_EndPoint;

	vtkSmartPointer<mis3DPlanParametricFunction> m_PlanParamFunc = vtkSmartPointer<mis3DPlanParametricFunction>::New();
	vtkSmartPointer<vtkParametricFunctionSource> m_PlanSource = vtkSmartPointer<vtkParametricFunctionSource>::New();
	vtkSmartPointer<vtkTransformPolyDataFilter> m_Polytransformer = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	vtkSmartPointer<vtkTransform> m_Transform = vtkSmartPointer<vtkTransform>::New();
	vtkSmartPointer<vtkCylinderSource> m_LineSource = vtkSmartPointer<vtkCylinderSource>::New();
	vtkSmartPointer<vtkAppendPolyData> m_AppendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkMapper> m_LineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	bool m_ShowDirectionAxis = false;
};

