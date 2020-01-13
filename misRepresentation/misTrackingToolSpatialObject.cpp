#include "StdAfx.h"
#include "misTrackingToolSpatialObject.h"

#include "misFileReader.h"
#include "misToolFileAddressUtility.h"
#include "misVisualizationResourceManager.h"

misTrackingToolSpatialObject::misTrackingToolSpatialObject(void)
{
	m_ToolFinalTransform = vtkSmartPointer<vtkTransform>::New();
}


misTrackingToolSpatialObject::~misTrackingToolSpatialObject(void)
{
}

void misTrackingToolSpatialObject::CreateRepresentation()
{
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetDirection(0, 0, 1);
	coneSource->SetCenter(0, 0, -m_ToolLength / 2);
	coneSource->SetHeight(m_ToolLength);
	coneSource->SetAngle(3);
	coneSource->SetResolution(8);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(coneSource->GetOutput());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(.7, .5, .0);
	
	AddProp(actor);
	m_RepresentationProp = actor;
}

void misTrackingToolSpatialObject::UpdateRepresentation(vtkSmartPointer<vtkTransform> toolFinalTransform)
{
	if (!m_RepresentationProp)
		return;
	m_ToolFinalTransform = toolFinalTransform;
	m_RepresentationProp->SetUserTransform(m_ToolFinalTransform);
}

void misTrackingToolSpatialObject::SetToolLength( double length )
{
	m_ToolLength = length;
	CreateRepresentation();
}

double misTrackingToolSpatialObject::GetToolLength()
{
	return m_ToolLength;
}
