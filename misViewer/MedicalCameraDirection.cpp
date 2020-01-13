#include "stdafx.h"
#include "MedicalCameraDirection.h"

using namespace parcast;

MedicalCameraDirection::MedicalCameraDirection(std::shared_ptr<I3DViewer> _3DViewer)
	:m_3DViewer(_3DViewer)
{
}


MedicalCameraDirection::~MedicalCameraDirection()
{
}

// set camera point in to xPoint
void MedicalCameraDirection::SetSupriorView()
{
	if (!(m_3DViewer->GetRenderer()))
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 1, 0);
	const auto bounding = m_3DViewer->GetBoundingBox();
	const auto focal = m_3DViewer->GetFocalPoint();

	const double height = bounding[5] - bounding[4];
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0], focal[1], focal[2] - height * m_3DViewer->GetScaleCameraPosition());
	m_3DViewer->GetRenderer()->GetRenderWindow()->Render();
}

// set camera point in to yPoint
void MedicalCameraDirection::SetInferiorView()
{
	if (!(m_3DViewer->GetRenderer()))
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 1, 0);
	const auto bounding = m_3DViewer->GetBoundingBox();

	const double height = bounding[5] - bounding[4];
	const auto focal = m_3DViewer->GetFocalPoint();

	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0], focal[1], focal[2] + height * m_3DViewer->GetScaleCameraPosition());
	m_3DViewer->GetRenderer()->GetRenderWindow()->Render();
}

// set camera point in to ZPoint  
void MedicalCameraDirection::SetAnteriorView()
{
	if (!m_3DViewer->GetRenderer())
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	double bounds[6];

	if (m_MainRepresentation)
		m_MainRepresentation->GetBoundingBox(bounds);
	else
	{
		bounds[0] = bounds[2] = bounds[4] = 0;
		bounds[1] = bounds[3] = bounds[5] = 500;
	}
	const auto focal = m_3DViewer->GetFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 0, -1);
	const auto width = bounds[3] - bounds[2];
	const auto y = focal[1] + width * m_3DViewer->GetScaleCameraPosition();
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(focal[0], y, focal[2]);
}

void MedicalCameraDirection::SetPosteriorView()
{
	if (!m_3DViewer->GetRenderer())
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);

	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 0, -1);
	const auto focal = m_3DViewer->GetFocalPoint();
	double bounds[6];
	if (m_MainRepresentation)
	{
		m_MainRepresentation->GetBoundingBox(bounds);
	}
	const auto width = bounds[3] - bounds[2];
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0], focal[1] - width * m_3DViewer->GetScaleCameraPosition(), focal[2]);
}

// set camera point in to xPoint
void MedicalCameraDirection::SetLeftView()
{
	if (!m_3DViewer->GetRenderer())
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	const auto focal = m_3DViewer->GetFocalPoint();
	const auto bounding = m_3DViewer->GetBoundingBox();
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 0, -1);
	const double xDirectionWidth = (bounding[1] - bounding[0]);
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0] + xDirectionWidth * m_3DViewer->GetScaleCameraPosition(), focal[1], focal[2]);
}

// set camera point in to yPoint
void MedicalCameraDirection::SetRightView()
{
	if (!m_3DViewer->GetRenderer())
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();
	m_3DViewer->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	const auto focal = m_3DViewer->GetFocalPoint();
	const auto bounding = m_3DViewer->GetBoundingBox();
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 0, -1);
	const double xDirectionWidth = bounding[1] - bounding[0];
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0] - xDirectionWidth * m_3DViewer->GetScaleCameraPosition(), focal[1], focal[2]);
}

void MedicalCameraDirection::SetDefaultVeiw()
{
	SetAnteriorView();
}

void MedicalCameraDirection::SetMainRepresentation(std::shared_ptr<IRepresentation> val)
{
	m_MainRepresentation = val;
}
