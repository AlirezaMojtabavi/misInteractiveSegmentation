#include "StdAfx.h"
#include "misNavigationState.h"

misNavigationState::misNavigationState() 
	: m_IsPlanEndPointSet(false), 
	m_IsPlanStartPointSet(false), 
	m_IsToolOrientationSet(false), 
	m_IsToolTipPositionSet(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_ToolTipPosition[i] = m_NormalToolOrientation[i] = m_PlanStartPoint[i] = m_PlanEndPoint[i] = 0;
	}
}

const double* misNavigationState::GetPlanStartPoint() const
{
	return m_PlanStartPoint;
}

void misNavigationState::SetPlanStartPoint( double *startPoint )
{
	std::copy(startPoint, startPoint + 3, m_PlanStartPoint);
	m_IsPlanStartPointSet = true;
}

const double * misNavigationState::GetPlanEndPoint() const
{
	return m_PlanEndPoint;
}

void misNavigationState::SetPlanEndPoint( double *endPoint )
{
	std::copy(endPoint, endPoint + 3, m_PlanEndPoint);
	m_IsPlanEndPointSet = true;
}

const double* misNavigationState::GetToolNormalDirection() const
{
	return m_NormalToolOrientation;
}

void misNavigationState::SetToolNormalDirection( double *normalDirection )
{
	//std::copy(normalDirection, normalDirection + 3, m_NormalToolOrientation);
	std::copy(normalDirection, normalDirection + 3, m_DejitterizedNormalToolOrientation);
	std::copy(m_DejitterizedNormalToolOrientation, m_DejitterizedNormalToolOrientation + 3, m_NormalToolOrientation);
	m_IsToolOrientationSet = true;
}

const double * misNavigationState::GetToolTipPosition() const
{
	return m_ToolTipPosition;
}

void misNavigationState::SetToolTipPosition( double *position )
{
	//std::copy(position, position + 3, m_ToolTipPosition);
	std::copy(position, position + 3, m_DejitterizedToolTipPosition);
	std::copy(m_DejitterizedToolTipPosition, m_DejitterizedToolTipPosition + 3, m_ToolTipPosition);
	m_IsToolTipPositionSet = true;
}

bool misNavigationState::IsInitialized() const
{
	return m_IsPlanStartPointSet && m_IsPlanEndPointSet;// && m_IsToolOrientationSet && m_IsToolTipPositionSet;
}

void misNavigationState::CalculatePlanNormalDirection( double direction[3] )
{
	vtkMath::Subtract(m_PlanEndPoint, m_PlanStartPoint, direction);
	vtkMath::Normalize(direction);
}

double misNavigationState::CalculatePlanLength()
{
	double distance2 = vtkMath::Distance2BetweenPoints(m_PlanEndPoint, m_PlanStartPoint);
	double length = std::sqrt(distance2);
	return length;
}
