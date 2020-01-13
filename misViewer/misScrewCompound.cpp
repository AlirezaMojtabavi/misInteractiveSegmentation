#include "stdafx.h"
#include "misScrewCompound.h"
#include "misScrewRepresentation.h"
#include "PlanTransformCalculator.h"

misScrewCompound::misScrewCompound(
	std::shared_ptr<IImplantSource> implantSource,
	const std::string uid,
	std::shared_ptr<IPlanWidgetRepresentation> screwRepresentation):
	m_ImplantSource(implantSource), m_LineWidget(nullptr), m_Selected(true), m_ScrewUID(uid), m_ScrewRepresentation(screwRepresentation)
{
	m_LineWidget = misPlanWidget::New();
	m_LineWidget->SetLineWidgetUID(m_ScrewUID);

	m_TransformMatrix->Identity();
}

misScrewCompound::~misScrewCompound(void)
{
	m_LineWidget->Delete();
}

void misScrewCompound::SetRotationStateValues()
{
	m_ScrewRepresentation->SetInteractionType(Rotation);
}

void misScrewCompound::SetExtendStateValues(double maxLineLen)
{
	m_ScrewRepresentation->SetInteractionType(Extend);
	m_ScrewRepresentation->SetMaxAllowedLineLen(maxLineLen);
}

void misScrewCompound::SetPositionStateValue()
{
	m_ScrewRepresentation->SetInteractionType(Position);
}

void misScrewCompound::SetFreeStateValue()
{
	if (m_ScrewRepresentation)
		m_ScrewRepresentation->SetInteractionType(Free);
}

void misScrewCompound::SetScrewWidget(misScrewWidgetData screwWidgetNewVal)
{
	if (m_ScrewRepresentation)
	{
		m_ScrewRepresentation->SetPointsWorldPosition(
			screwWidgetNewVal.GetStartPoint().data, screwWidgetNewVal.GetEndPoint().data);
		m_ScrewRepresentation->SetInteractionType(screwWidgetNewVal.GetInterationType());
		m_TransformMatrix->DeepCopy(screwWidgetNewVal.GetTransformMatrix());
	}
}

double* misScrewCompound::GetPoint1WorldPosition() const 
{
	if (m_ScrewRepresentation)
		return  m_ScrewRepresentation->GetPoint1WorldPosition();
	return nullptr;
}

double* misScrewCompound::GetPoint2WorldPosition() const 
{
	if (m_ScrewRepresentation)
	{
		return  m_ScrewRepresentation->GetPoint2WorldPosition();
	}
	return nullptr;
}

ScrewWidgetInteractionType misScrewCompound::GetInteractionType() const
{
	ScrewWidgetInteractionType resType = Free;
	if (m_ScrewRepresentation)
		return m_ScrewRepresentation->GetInteractionType();
	return resType;
}

misPlanWidget* misScrewCompound::GetWidget() const
{
	if (m_LineWidget)
		return m_LineWidget;
	return nullptr;
}

vtkMatrix4x4* misScrewCompound::GetTransformMatrix() const
{
	if (m_TransformMatrix)
	{
		return m_TransformMatrix;
	}
	return vtkMatrix4x4::New();
}



void misScrewCompound::SetInteractor(vtkRenderWindowInteractor*	pRenderWindowInteractor)
{
	if (!m_LineWidget || !pRenderWindowInteractor)
		return;
	m_LineWidget->SetInteractor(pRenderWindowInteractor);
	m_LineWidget->SetRepresentation(m_ScrewRepresentation.get());
	m_LineWidget->On();
}

void misScrewCompound::Off()
{
	m_LineWidget->Off();
}

void misScrewCompound::On()
{
	m_LineWidget->On();
}

void misScrewCompound::SetColor(misColorStruct screwColor)
{
	if (m_ScrewRepresentation)
		m_ScrewRepresentation->SetLineColor(screwColor.red / 255.0, screwColor.green / 255.0, screwColor.blue / 255.0);
}

void misScrewCompound::SetWidth(const double& width)
{
	if (m_ScrewRepresentation)
		m_ScrewRepresentation->SetScrewDiameter(width);
}

misUID misScrewCompound::GetScrewUID() const
{
	return m_ScrewUID;
}

void misScrewCompound::SetLocked(bool finalized)
{
	m_ScrewRepresentation->SetScrewPlacementIsFinalized(finalized);
}

void misScrewCompound::HighlightScrew(bool highlight)
{
	m_ScrewRepresentation->HighlightLine(highlight);
}

void misScrewCompound::SetSelected(bool selected)
{
	m_Selected = selected;
}

bool misScrewCompound::GetSelected() const
{
	return m_Selected;
}


void misScrewCompound::SetEntry(parcast::PointD3 point)
{
	auto targetPoint = m_ImplantSource->GetTarget();
	double target[3] = { targetPoint[0], targetPoint[1], targetPoint[2] };
	double entry[3] = {point[0], point[1], point[2]};
	
	m_ScrewRepresentation->SetPointsWorldPosition(entry, target);
}

void misScrewCompound::SetTarget(parcast::PointD3 point)
{
	auto entryPoint = m_ImplantSource->GetEntry();
	double entry[3] = { entryPoint[0], entryPoint[1], entryPoint[2] };
	double target[3] = { point[0], point[1], point[2] };

	m_ScrewRepresentation->SetPointsWorldPosition(entry, target);
}


void misScrewCompound::SetTargetRadius(double radius)
{
	m_ImplantSource->SetTargetRadius(radius);
}

