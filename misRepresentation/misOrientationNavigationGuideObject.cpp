#include "StdAfx.h"
#include "misOrientationNavigationGuideObject.h"

#include "misException.h"
#include "misVisualizationResourceManager.h"

misOrientationNavigationGuideObject::misOrientationNavigationGuideObject()
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


vtkProperty* misOrientationNavigationGuideObject::GetActorProperty()
{
	return m_ArrowActor->GetProperty();
}

void misOrientationNavigationGuideObject::UpdateRepresentation()
{
	// Take two vectors T and P:
	// Let T be GetToolNormalDirection() and P be PlanNormalDirection, i.e., GetPlanEndPoint() - GetPlanStartPoint().
	// We need the transform to rotate a vector lying on the X axis to align it with D = T x (T x P), that is the vector in the
	// common plane of T and P, and at the same time orthogonal to T and swiping the tool tail towards P. To achieve this, we first 
	// compute the destination direction vector (D), then we compute the angle it makes with the X axis, D~X. Now we need the vector 
	// perpendicular to the common plane of D and X, i.e. W = D x X.
	// Then the transform should rotate its input vector with an angle of D~X around the vector W.
	// Finally, the transform can scale the vector using the given scale factor calculated based on the threshold angle.
	// The last step translates the guide mark arrow the actual position of the tool in space.

	if (!GetNavigationState() || !GetNavigationState()->IsInitialized())
		throw misException("misOrientationNavigationGuideObject not properly initialized. NavigationState null.");

	double toolNormalDirection[3];	// T
	std::copy(GetNavigationState()->GetToolNormalDirection(), 
		GetNavigationState()->GetToolNormalDirection() + 3, toolNormalDirection);

	double planNormalDirection[3];	// P
	GetNavigationState()->CalculatePlanNormalDirection(planNormalDirection);

	double destinationDirectionVector[3];	// Compute D = T x (T x P) and put it in destinationDirectionVector
	vtkMath::Cross(toolNormalDirection, planNormalDirection, destinationDirectionVector);	// T x P
	vtkMath::Cross(toolNormalDirection, destinationDirectionVector, destinationDirectionVector);	// T x (T x P)

	double xUnit[] = { 1, 0, 0 };
	vtkSmartPointer<vtkTransform> transform = misMathUtils::RotationTransformFromVectors(xUnit, destinationDirectionVector);

	double dividingAngle = misMathUtils::ComputeAngleBetweenVectors(toolNormalDirection, planNormalDirection);	// For scaling

	// The scale factor is the ratio of the dividing angle and the given threshold angle, clipped between min and max.
	double scaleFactor = m_Scale * misMathUtils::ClipValue(dividingAngle / m_Properties.GetThresholdAngle(), 
		m_Properties.GetMinimumGuideScale(), m_Properties.GetMaximumGuideScale());
	transform->Scale(scaleFactor, scaleFactor, scaleFactor);	// Perform the scaling on the transform

	transform->PostMultiply();	// Translation should take place after the rotation.
	//const double *toolTipPosition = GetNavigationState()->GetToolTipPosition();
	//vtkMath::MultiplyScalar(toolNormalDirection, -m_ToolLength);
	//
	//vtkMath::Add(toolTipPosition, toolNormalDirection, m_GuideStartPoint);
	transform->Translate(m_GuideStartPoint[0], m_GuideStartPoint[1], m_GuideStartPoint[2]);

	const double GuideLength = 70;
	vtkMath::MultiplyScalar(xUnit, GuideLength);
	transform->TransformPoint(xUnit, m_GuideEndPoint);

	m_ArrowActor->SetUserTransform(transform);

	std::stringstream formatterStream;
	formatterStream << std::fixed << std::setprecision(1) << dividingAngle;
	m_CaptionString = formatterStream.str();
	m_CaptionActor->SetCaption(m_CaptionString.c_str());
	m_CaptionActor->SetAttachmentPoint(m_GuideStartPoint);
}

vtkSmartPointer<vtkCaptionActor2D> misOrientationNavigationGuideObject::GetCaptionActor()
{
	return m_CaptionActor;
}

void misOrientationNavigationGuideObject::GetGuideEndPoint( double * endPoint )
{
	
	endPoint[0] = m_GuideEndPoint[0];
	endPoint[1] = m_GuideEndPoint[1];
	endPoint[2] = m_GuideEndPoint[2];
}

void misOrientationNavigationGuideObject::SetProperties( const misOrientationNavigationGuideObjectSettings &newSettings )
{
	m_Properties = newSettings;
	m_CaptionActor->GetCaptionTextProperty()->SetColor(
		m_Properties.GetCaptionColour()[0], m_Properties.GetCaptionColour()[1], m_Properties.GetCaptionColour()[2]);
	m_CaptionActor->SetPosition(m_Properties.GetCaptionPosition()[0], m_Properties.GetCaptionPosition()[1]);
	m_CaptionActor->SetPosition2(m_Properties.GetCaptionSize()[0], m_Properties.GetCaptionSize()[1]);
	m_ArrowActor->GetProperty()->SetColor(
		m_Properties.GetGuideArrowColour()[0], m_Properties.GetGuideArrowColour()[1], m_Properties.GetGuideArrowColour()[2]);
}

const misOrientationNavigationGuideObjectSettings & misOrientationNavigationGuideObject::GetProperties() const
{
	return m_Properties;
}
