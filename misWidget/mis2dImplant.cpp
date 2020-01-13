#include "stdafx.h"
#include "mis2dImplant.h"

#include "misPlanMapper.h"
#include "BiopsyToolDetector.h"

mis2DImplant::mis2DImplant(std::string const& shaderPath, std::weak_ptr<ICornerProperties> cornerProperties, parcast::PlanSettingParam biopsyPlanParam, bool displayCross)
{
	m_PlanMapper = new misPlanMapper(cornerProperties, shaderPath, biopsyPlanParam, displayCross);
 }

mis2DImplant::~mis2DImplant()
{
	delete m_PlanMapper;
}

void mis2DImplant::SetEntry(const parcast::PointD3& point)
{
	m_StartPoint = point;
	m_PlanMapper->SetStartPoint(
		parcast::Point<float, 3>(static_cast<float>(point[0]), static_cast<float>(point[1]), static_cast<float>(point[2])));
}

void mis2DImplant::SetTarget(const parcast::PointD3& point)
{
	m_EndPoint = point;
	m_PlanMapper->SetEndPoint(
		parcast::Point<float, 3>(static_cast<float>(point[0]), static_cast<float>(point[1]), static_cast<float>(point[2])));
}

void mis2DImplant::SetRadius(double radius)
{
	m_Radius = radius;
	m_PlanMapper->SetRadius(radius);
}

vtkSmartPointer<vtkMapper> mis2DImplant::GetMapper() const noexcept
{
	return m_PlanMapper;
}

void mis2DImplant::SetCurrentPoint(const parcast::PointD3& point)
{
	m_CurrentPoint = point;
	m_PlanMapper->SetCurrentPoint(
		parcast::Point<float, 3>(static_cast<float>(point[0]), static_cast<float>(point[1]), static_cast<float>(point[2])));
}

void mis2DImplant::SetInterSectionPoint(const parcast::PointD3& point)
{
	m_InterSectionPoint = point;
	m_PlanMapper->SetInterSectionPoint(
		parcast::Point<float, 3>(static_cast<float>(point[0]), static_cast<float>(point[1]), static_cast<float>(point[2])));
}

void mis2DImplant::SetNormalPlane(const parcast::VectorD3& vector)
{
	m_NormalPlane = vector;
	m_PlanMapper->SetNormalPlane(
		parcast::Vector<float, 3>(static_cast<float>(vector[0]), static_cast<float>(vector[1]), static_cast<float>(vector[2])));
}

parcast::PointD3 mis2DImplant::GetEntry() const noexcept
{
	return m_StartPoint;
}

parcast::PointD3 mis2DImplant::GetTarget() const noexcept
{
	return m_EndPoint;
}

double mis2DImplant::GetRadius() const noexcept
{
	return m_Radius;
}

void mis2DImplant::SetTargetRadius(double radius)
{
	m_PlanMapper->SetTargetRadius(radius);
}