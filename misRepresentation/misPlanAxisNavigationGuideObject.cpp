#include "StdAfx.h"
#include "misPlanAxisNavigationGuideObject.h"

#include "misVisualizationResourceManager.h"

misPlanAxisNavigationGuideObject::misPlanAxisNavigationGuideObject(void)
{
	m_ArrowActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkPolyData> guideArrow = misVisualizationResourceManager::GetInstance()->GetArrowStl();
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(guideArrow);
	m_ArrowActor->SetMapper(mapper);
	AddProp(m_ArrowActor);

	m_CaptionActor = vtkSmartPointer<vtkCaptionActor2D>::New();
	m_CaptionActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
	// We don't want the caption to move around with the attachment point (the arrow start); we make it absolute.
	m_CaptionActor->GetPositionCoordinate()->SetReferenceCoordinate(NULL);
	m_CaptionActor->LeaderOff();
	AddProp(m_CaptionActor);

}

misPlanAxisNavigationGuideObject::~misPlanAxisNavigationGuideObject(void)
{
}

void misPlanAxisNavigationGuideObject::UpdateRepresentation()
{
	const double * toolTipPosition = GetNavigationState()->GetToolTipPosition();	// (x, y, z)
	
	double nearestPointOnTheAxis[3];
	GetNavigationState()->CalculateToolTipProjectionOnPlanAxis(nearestPointOnTheAxis);
	
	// The translation vector for traveling from tool tip to plan start point
	double translationDirection[3];
	vtkMath::Subtract(nearestPointOnTheAxis, toolTipPosition, translationDirection);

	double xUnit[] = { 1, 0, 0 };
	vtkSmartPointer<vtkTransform> transform = misMathUtils::RotationTransformFromVectors(xUnit, translationDirection);

	double distanceFromPlanAxis = std::sqrt(vtkMath::Distance2BetweenPoints(toolTipPosition, nearestPointOnTheAxis));

	// We scale the the guide mark based on the distance from the axis. The distance is clipped between min and max.
	double scaleFactor = misMathUtils::ClipValue(distanceFromPlanAxis / m_Properties.GetThresholdDistance(), 
		m_Properties.GetMinimumGuideScale(), m_Properties.GetMaximumGuideScale());
	transform->Scale(scaleFactor, scaleFactor, scaleFactor);

	transform->PostMultiply();	// Translation should take place after the rotation.
	transform->Translate(toolTipPosition);

	double supposedGuideArrowAxis[] = { 70, 0, 0 };
	transform->TransformPoint(supposedGuideArrowAxis, m_GuideEndPoint);

	m_ArrowActor->SetUserTransform(transform);

	std::stringstream formatterStream;
	formatterStream << std::fixed << std::setprecision(1) << distanceFromPlanAxis << "mm";
	m_CaptionString = formatterStream.str();
	m_CaptionActor->SetCaption(m_CaptionString.c_str());
	m_CaptionActor->SetAttachmentPoint(toolTipPosition[0], toolTipPosition[1], toolTipPosition[2]);

	std::copy(toolTipPosition, toolTipPosition + 3, m_GuideStartPoint);
}

void misPlanAxisNavigationGuideObject::GetGuideStartPoint( double *startPoint )
{
	startPoint[0] = m_GuideStartPoint[0];
	startPoint[1] = m_GuideStartPoint[1];
	startPoint[2] = m_GuideStartPoint[2];
}

void misPlanAxisNavigationGuideObject::GetGuideEndPoint( double *endPoint )
{
	//std::copy(m_GuideEndPoint, m_GuideEndPoint + 3, endPoint);
	endPoint[0] = m_GuideEndPoint[0];
	endPoint[1] = m_GuideEndPoint[1];
	endPoint[2] = m_GuideEndPoint[2];
}

void misPlanAxisNavigationGuideObject::SetProperties( const misPlanAxisNavigationGuideObjectProperties &newSettings )
{
	m_Properties = newSettings;
	m_CaptionActor->GetCaptionTextProperty()->SetColor(
		m_Properties.GetCaptionColour()[0], m_Properties.GetCaptionColour()[1], m_Properties.GetCaptionColour()[2]);
	m_CaptionActor->SetPosition(m_Properties.GetCaptionPosition()[0], m_Properties.GetCaptionPosition()[1]);
	m_CaptionActor->SetPosition2(m_Properties.GetCaptionSize()[0], m_Properties.GetCaptionSize()[1]);
	m_ArrowActor->GetProperty()->SetColor(
		m_Properties.GetGuideArrowColour()[0], m_Properties.GetGuideArrowColour()[1], m_Properties.GetGuideArrowColour()[2]);
}

const misPlanAxisNavigationGuideObjectProperties & misPlanAxisNavigationGuideObject::GetProperties() const
{
	return m_Properties;
}
