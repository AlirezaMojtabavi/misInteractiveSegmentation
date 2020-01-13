#include "StdAfx.h"
#include "misPlannedScrewSpatialObject.h"

#include "misMathUtils.h"

misPlannedScrewSpatialObject::misPlannedScrewSpatialObject(void)
{
	m_PlanStartPoint[0] = m_PlanStartPoint[1] = m_PlanStartPoint[2] = 0;
	m_PlanEndPoint[0] = m_PlanEndPoint[1] = m_PlanEndPoint[2] = 0;
	
	m_StartPointActor = vtkSmartPointer<vtkActor>::New();
	AddProp(m_StartPointActor);

	m_ShaftActor = vtkSmartPointer<vtkActor>::New();
	m_ShaftActor->GetProperty()->SetColor(.5, .2, .6);
	//AddProp(m_ShaftActor);

	m_EndPointActor = vtkSmartPointer<vtkActor>::New();
	AddProp(m_EndPointActor);

	SetScale(1);
}


misPlannedScrewSpatialObject::~misPlannedScrewSpatialObject(void)
{
}

void misPlannedScrewSpatialObject::UpdateRepresentation()
{
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->Translate(m_PlanStartPoint);
	transform->Scale(m_Scale, m_Scale, m_Scale);
	m_StartPointActor->SetUserTransform(transform);

	vtkSmartPointer<vtkTransform> transform2 = vtkSmartPointer<vtkTransform>::New();
	transform2->Translate(m_PlanEndPoint);
	transform2->Scale(m_Scale, m_Scale, m_Scale);
	m_EndPointActor->SetUserTransform(transform2);
}

void misPlannedScrewSpatialObject::CreateRepresentation()
{
	vtkSmartPointer<vtkSphereSource> startPointSphere = vtkSmartPointer<vtkSphereSource>::New();
	startPointSphere->SetRadius(m_Properties.GetStartPointRadius());
	vtkSmartPointer<vtkPolyDataMapper> startPointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	startPointMapper->SetInputData(startPointSphere->GetOutput());
	m_StartPointActor->SetMapper(startPointMapper);

	vtkSmartPointer<vtkSphereSource> endPointSphere = vtkSmartPointer<vtkSphereSource>::New();
	endPointSphere->SetCenter(m_PlanEndPoint);
	endPointSphere->SetRadius(m_Properties.GetEndPointRadius());
	vtkSmartPointer<vtkPolyDataMapper> endPointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	endPointMapper->SetInputData(endPointSphere->GetOutput());
	m_EndPointActor->SetMapper(endPointMapper);

	vtkSmartPointer<vtkCylinderSource> planShaft = vtkSmartPointer<vtkCylinderSource>::New();

	double planLength = std::sqrt(vtkMath::Distance2BetweenPoints(m_PlanEndPoint, m_PlanStartPoint));
	planShaft->SetHeight(planLength);
	double shaftCentre[3];
	misMathUtils::ComputeMidpoint(m_PlanStartPoint, m_PlanEndPoint, shaftCentre);
	planShaft->SetCenter(shaftCentre);
	planShaft->SetRadius(m_Properties.GetShaftRadius());

	vtkSmartPointer<vtkPolyDataMapper> shaftMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	shaftMapper->SetInputData(planShaft->GetOutput());
	m_ShaftActor->SetMapper(shaftMapper);

	// Since the cylinder lies by default on the Y axis, we first align it with X and then rotate it to align it with plan axis.
	double planAxis[3];
	double unitY[] = { 0, 1, 0 } ;
	vtkMath::Subtract(m_PlanEndPoint, m_PlanStartPoint, planAxis);
	vtkSmartPointer<vtkTransform> transform = misMathUtils::RotationTransformFromVectors(unitY, planAxis);
	m_ShaftActor->SetUserTransform(transform);
}

void misPlannedScrewSpatialObject::SetProperties( const misPlannedScrewSpatialObjectProperties &newSettings )
{
	m_Properties = newSettings;
	m_StartPointActor->GetProperty()->SetColor(
		m_Properties.GetStartPointColour()[0], m_Properties.GetStartPointColour()[1], m_Properties.GetStartPointColour()[2]);
	m_EndPointActor->GetProperty()->SetColor(
		m_Properties.GetEndPointColour()[0], m_Properties.GetEndPointColour()[1], m_Properties.GetEndPointColour()[2]);
	CreateRepresentation();
}

const misPlannedScrewSpatialObjectProperties & misPlannedScrewSpatialObject::GetProperties() const
{
	return m_Properties;
}
