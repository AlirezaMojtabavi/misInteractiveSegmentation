#include "StdAfx.h"
#include "misPlanStartNavigationGuideObject.h"

#include "misMathUtils.h"
#include "misVisualizationResourceManager.h"

misPlanStartNavigationGuideObject::misPlanStartNavigationGuideObject(void)
{
	m_Actor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkPolyData> guideArrow = misVisualizationResourceManager::GetInstance()->GetArrowStl();
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(guideArrow);
	m_Actor->SetMapper(mapper);
	m_Actor->GetProperty()->SetColor(.1, .6, .7);
	AddProp(m_Actor);

	m_CaptionActor = vtkSmartPointer<vtkCaptionActor2D>::New();
	m_CaptionActor->GetCaptionTextProperty()->SetColor(.2, .7, .8);
	m_CaptionActor->SetPosition(-200, 150);
	m_CaptionActor->SetPosition2(.12, 0.05);
	AddProp(m_CaptionActor);

	SetThresholdDistance(50);
	SetMinimumGuideScale(.3);
	SetMaximumGuideScale(1.2);
}

misPlanStartNavigationGuideObject::~misPlanStartNavigationGuideObject(void)
{
}

void misPlanStartNavigationGuideObject::UpdateRepresentation()
{
	const double * planStartPoint = GetNavigationState()->GetPlanStartPoint();
	const double * toolTipPosition = GetNavigationState()->GetToolTipPosition();

	// The translation vector for traveling from tool tip to plan start point
	double translationDirection[3];
	for (int i = 0; i < 3; i++)
		translationDirection[i] = planStartPoint[i] - toolTipPosition[i];

	double unitX[] = { 1, 0, 0 };
	vtkSmartPointer<vtkTransform> transform = misMathUtils::RotationTransformFromVectors(unitX, translationDirection);

	double distance = std::sqrt(vtkMath::Distance2BetweenPoints(toolTipPosition, planStartPoint));
	double scaleFactor = misMathUtils::ClipValue(distance / m_ThresholdDistance, m_MinimumGuideScale, m_MaximumGuideScale);
	transform->Scale(scaleFactor, scaleFactor, scaleFactor);

	transform->PostMultiply();	// Translation should take place after the rotation.
	transform->Translate(toolTipPosition);

	m_Actor->SetUserTransform(transform);

	std::stringstream formatterStream;
	formatterStream << std::fixed << std::setprecision(1) << distance;
	m_CaptionString = formatterStream.str();
	m_CaptionActor->SetCaption(m_CaptionString.c_str());
	m_CaptionActor->SetAttachmentPoint(toolTipPosition[0], toolTipPosition[1], toolTipPosition[2]);
}

vtkProperty* misPlanStartNavigationGuideObject::GetActorProperty()
{
	return m_Actor->GetProperty();
}
