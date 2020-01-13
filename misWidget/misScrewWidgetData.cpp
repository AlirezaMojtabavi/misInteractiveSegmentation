#include "stdafx.h"
#include "misScrewWidgetData.h"

void misScrewWidgetData::Reset()
{
	m_TransformMatrix->Identity();
}

misSimplePointType misScrewWidgetData::GetStartPoint() const
{
	return m_StartPoint;
}

void misScrewWidgetData::SetStartPoint( misSimplePointType val )
{
	m_StartPoint = val;
}

void misScrewWidgetData::SetStartPoint( double const* point )
{
	m_StartPoint.SetPoint(point);
}

misSimplePointType misScrewWidgetData::GetEndPoint() const
{
	return m_EndPoint;
}

void misScrewWidgetData::SetEndPoint( misSimplePointType val )
{
	m_EndPoint = val;
}

void misScrewWidgetData::SetEndPoint(double const* val )
{
	m_EndPoint.SetPoint(val);
}

vtkSmartPointer<vtkMatrix4x4> misScrewWidgetData::GetTransformMatrix() const
{
	return m_TransformMatrix;
}

void misScrewWidgetData::DeepCopyTransformMatrix( vtkSmartPointer<vtkMatrix4x4> val )
{
	m_TransformMatrix = val;
}

ScrewWidgetSourceType misScrewWidgetData::GetSourceType() const
{
	return m_sourceType;
}

void misScrewWidgetData::SetSourceType( ScrewWidgetSourceType val )
{
	m_sourceType = val;
}

ScrewWidgetInteractionType misScrewWidgetData::GetInterationType() const
{
	return m_interationType;
}

void misScrewWidgetData::SetInterationType( ScrewWidgetInteractionType val )
{
	m_interationType = val;
}

misUID misScrewWidgetData::GetScrewUID() const
{
	return m_ScrewUID;
}

void misScrewWidgetData::SetScrewUID( misUID val )
{
	m_ScrewUID = val;
}

double misScrewWidgetData::GetScrewDiameter() const
{
	return screwDiameter;
}

void misScrewWidgetData::SetScrewDiameter( double val )
{
	screwDiameter = val;
}

double misScrewWidgetData::GetTargetRadius() const
{
	return m_TargetRadius;
}

void misScrewWidgetData::SetTargetRadius(double val)
{
	m_TargetRadius = val;
}

void misScrewWidgetData::SetStartPointModified()
{
	m_StartPointModified = true;
}

void misScrewWidgetData::SetEndPointModified()
{
	m_EndPointModified = true;
}

bool misScrewWidgetData::IsStartPointModified() const
{
	return m_StartPointModified;
}

bool misScrewWidgetData::IsEndPointModified() const
{
	return m_EndPointModified;
}

void misScrewWidgetData::TransformPlan(vtkSmartPointer<vtkTransform> transfom)
{

	double* transformedData = transfom->TransformDoublePoint(m_StartPoint.data);
	m_StartPoint.data[0] = transformedData[0];
	m_StartPoint.data[1] = transformedData[1];
	m_StartPoint.data[2] = transformedData[2];

	transformedData = transfom->TransformDoublePoint(m_EndPoint.data);
	m_EndPoint.data[0] = transformedData[0];
	m_EndPoint.data[1] = transformedData[1];
	m_EndPoint.data[2] = transformedData[2];
	m_TransformMatrix->DeepCopy(transfom->GetMatrix());
 
}

misScrewWidgetData::misScrewWidgetData()
	:m_sourceType(Line)
{
	m_TransformMatrix = vtkMatrix4x4::New();
	Reset();
}
