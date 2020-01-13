#include "stdafx.h"
#include "mis3DImplant.h"

#include "BusinessEntities\Point.h"
#include "misMathUtils.h"

mis3DImplant::mis3DImplant(
	std::unique_ptr<parcast::I3DPlanCrossSectionFunction> crossSectionFunction, bool showDirectionAxis, 
	double lineRadius, double lineHeight)
	:m_ShowDirectionAxis(showDirectionAxis),
	m_LineRadius(lineRadius),
	m_LineHeight(lineHeight)
{
	m_PlanParamFunc->SetCrossSectionFucntion(std::move(crossSectionFunction));
	m_PlanSource->SetParametricFunction(m_PlanParamFunc);
	m_PlanParamFunc->SetRadius(m_Radius);
	if (m_ShowDirectionAxis)
	{
		m_LineSource->SetRadius(m_LineRadius);
		m_LineSource->SetHeight(m_LineHeight);
		m_LineSource->SetResolution(LineResolution);
	}

	m_LineMapper->SetInputConnection(m_Polytransformer->GetOutputPort());
}

vtkSmartPointer<vtkTransform> mis3DImplant::CalculateRotationMatrix(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint)
{
	auto const planVec = endPoint - startPoint;
	double const yAxis[] = { 0., 1.0, 0.0 };
	auto rotationMat = misMathUtils::RotationTransformFromVectors(yAxis, planVec.Elements());
	return rotationMat;
}

void mis3DImplant::RotateTranform(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint, vtkSmartPointer<vtkTransform>& transform)
{
	auto const rotation = CalculateRotationMatrix(startPoint, endPoint);
	transform->PostMultiply();
	transform->Concatenate(rotation);
}

void mis3DImplant::Update(const parcast::PointD3& startPoint, const parcast::PointD3& endPoint)
{
	m_PlanSource = vtkParametricFunctionSource::New();
	auto const planLength = (endPoint - startPoint).Length();
	m_PlanParamFunc->SetMaximumV(planLength);
	m_PlanSource->SetUResolution(m_NumberofSides);
	m_PlanSource->SetVResolution(static_cast<int>(planLength * 10.));
	m_PlanSource->SetParametricFunction(m_PlanParamFunc);
	m_PlanSource->Update();
	m_AppendFilter->RemoveAllInputs();
	m_AppendFilter->AddInputConnection(m_PlanSource->GetOutputPort());
	if(m_ShowDirectionAxis)
		m_AppendFilter->AddInputConnection(m_LineSource->GetOutputPort());
	m_AppendFilter->Update();

	m_Transform->Identity();
	RotateTranform(startPoint, endPoint, m_Transform);
	m_Transform->Translate(startPoint[0], startPoint[1], startPoint[2]);
	m_Polytransformer->SetTransform(m_Transform);
	m_Polytransformer->SetInputConnection(m_AppendFilter->GetOutputPort());
}

void mis3DImplant::SetRadius(double radius)
{
	m_Radius = radius;
	m_PlanParamFunc->SetRadius(radius);
	Update(m_StartPoint, m_EndPoint);
}

vtkSmartPointer<vtkMapper> mis3DImplant::GetMapper() const noexcept
{
	return m_LineMapper;
}

void mis3DImplant::SetCurrentPoint(const parcast::PointD3& point)
{
}

void mis3DImplant::SetInterSectionPoint(const parcast::PointD3& point)
{
}
void mis3DImplant::SetNormalPlane(const parcast::VectorD3& vector)
{
	
}

parcast::PointD3 mis3DImplant::GetEntry() const noexcept
{
	return m_StartPoint;
}

parcast::PointD3 mis3DImplant::GetTarget() const noexcept
{
	return m_EndPoint;
}

double mis3DImplant::GetRadius() const noexcept
{
	return m_Radius;
}

void mis3DImplant::SetTargetRadius(double radius)
{
}

void mis3DImplant::SetEntry(const parcast::PointD3& point)
{
	if (point == m_StartPoint)
	{
		return;
	}

	m_StartPoint = point;
	Update(m_StartPoint, m_EndPoint);
}

void mis3DImplant::SetTarget(const parcast::PointD3& point)
{
	if (point == m_EndPoint)
	{
		return;
	}

	m_EndPoint = point;
	Update(m_StartPoint, m_EndPoint);
}
