#include "stdafx.h"
#include "misCameraInteraction.h"

#include "misVisualizationUtils.h"
#include "misApplicationSetting.h"
#include "misCamera.h"
#include "misCameraMacher.h"

misCameraInteraction::misCameraInteraction()
	: ParallelPlaneScaleFactor(3.0)
{

	Reset();
}

void misCameraInteraction::UpdateView()
{
	if (!m_Camera || !m_CornerProperties->GetValidity())
		return;

	m_Camera->ParallelProjectionOn();
	m_Camera->SetParallelScale(m_CameraScale);
	UpdateCamera();

}

void misCameraInteraction::SetDefaultZoom()
{
	UpdatePlaneDimension();
	m_CameraScale = std::max(m_PlaneDimension[0], m_PlaneDimension[1]) / ParallelPlaneScaleFactor;
	m_CurrentZoomPercentage = 100;
	m_Camera->SetParallelScale(m_CameraScale);
}

void misCameraInteraction::UpdateCamera()
{
	misSimplePointType viewUp = m_CornerProperties->GetPlaneViewUp();
	const auto cameraPosition = m_CornerProperties->GetCameraPosition();
	const auto cameraFocalPoint = m_CornerProperties->GetCameraFocalPoint();
	m_Camera->SetPosition(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	m_Camera->SetFocalPoint(cameraFocalPoint[0], cameraFocalPoint[1], cameraFocalPoint[2]);
	m_Camera->SetViewUp(viewUp.data);
	m_Camera->OrthogonalizeViewUp();

}

void misCameraInteraction::SetAutoCameraScale(double pScale)
{
	m_CameraScale = pScale;
}

void misCameraInteraction::SetImageOrientation(IMAGEORIENTATION pImageOrientation)
{
	m_ImageOrientation = pImageOrientation;
}

void misCameraInteraction::SetCamera(vtkCamera* pCamera)
{
	m_Camera = pCamera;
}

void misCameraInteraction::SetPlaneCenter(PointType pPlaneCenter)
{
	m_PlaneCenter[0] = pPlaneCenter[0];
	m_PlaneCenter[1] = pPlaneCenter[1];
	m_PlaneCenter[2] = pPlaneCenter[2];
}

void misCameraInteraction::SetPlaneDimendion(double *pDim)
{
	if (pDim)
	{
		m_PlaneDimension[0] = pDim[0];
		m_PlaneDimension[1] = pDim[1];
		m_PlaneDimension[2] = pDim[2];
	}
	else
		_ASSERT(0 == 1);
}

bool misCameraInteraction::ResetZoomNeeded(int zoomPercentage)
{
	return zoomPercentage == 100;
}

void misCameraInteraction::UpdatePlaneDimension()
{
	if (m_CornerProperties->GetValidity() == true && m_ImageOrientation != UNKnownDirection)
	{
		auto planePoints = m_CornerProperties->GetPlanePoints(m_ImageOrientation);
		m_PlaneDimension[0] = misSimplePointType::EuclideanDistance(planePoints[0], planePoints[1]);
		m_PlaneDimension[1] = misSimplePointType::EuclideanDistance(planePoints[1], planePoints[2]);
	}
	else
	{
		m_PlaneDimension[0] = -1;
		m_PlaneDimension[1] = -1;
		m_PlaneDimension[2] = -1;
	}
}

void misCameraInteraction::SetCurrentZoomProportion(double pProportion)
{
	m_currentZoomProportion = pProportion;
}

double misCameraInteraction::GetCurrentZoomProportion() const
{
	return m_currentZoomProportion;
}

zoomStrct misCameraInteraction::UpdateZoomPercentageInGUI()
{
	zoomStrct zoomStr;
	zoomStr.percentage = GetCurrentZoomPercentage();
	zoomStr.proportion = GetCurrentZoomProportion();
	zoomStr.fromImageViewer = true;
	return zoomStr;

}

void misCameraInteraction::SetCurrentZoomPercentage(unsigned int pPercentage)
{

	m_CurrentZoomPercentage = pPercentage;

}

unsigned int misCameraInteraction::GetCurrentZoomPercentage() const
{

	return m_CurrentZoomPercentage;

}

vtkCamera* misCameraInteraction::GetCamera()
{
	if (m_Camera)
		return m_Camera;

	_ASSERT(0 == 1);
	return  NULL;
}

void misCameraInteraction::UpdateZoom(misZoomState pZoomState, double pWidgetCenter[3])
{
	if (!m_Camera)
		return;
	int nextZoomPercentage = 100; // default zoom, reset also means it
	switch (pZoomState)
	{
	case ZoomIn:
		nextZoomPercentage = m_ZoomService.FindNextZoomPercentage(m_CurrentZoomPercentage);
		break;

	case ZoomOut:
		nextZoomPercentage = m_ZoomService.FindPreviousZoomPercentage(m_CurrentZoomPercentage);
		break;
	}

	if (nextZoomPercentage == 0)
		return;

	if (pZoomState == ResetZoom)
	{
		if (ResetZoomNeeded(m_CurrentZoomPercentage))
			return;

		SetDefaultZoom();
		m_CornerProperties->SetSightLineIntersectionPointToPlaneCenter();
	}
	else
	{
		double scale = m_Camera->GetParallelScale();
		m_CameraScale = (scale * m_CurrentZoomPercentage) / nextZoomPercentage;
		m_Camera->SetParallelScale(m_CameraScale);
		m_CornerProperties->ResetSightLineIntersectionPoint();
	}
	m_CurrentZoomPercentage = nextZoomPercentage;
}

void misCameraInteraction::SetCameraFocalPoint(PointType pFocalPoint)
{
	_ASSERT(0 == 1);
	m_FocalPointCenter[0] = pFocalPoint[0];
	m_FocalPointCenter[1] = pFocalPoint[1];
	m_FocalPointCenter[2] = pFocalPoint[2];
}

void misCameraInteraction::SetCameraFocalPoint(double* pFocalPoint)
{
	_ASSERT(0 == 1);
	if (pFocalPoint)
	{
		m_FocalPointCenter[0] = pFocalPoint[0];
		m_FocalPointCenter[1] = pFocalPoint[1];
		m_FocalPointCenter[2] = pFocalPoint[2];
	}
	else
		_ASSERT(0 == 1);
}

void misCameraInteraction::SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp)
{
	if (pCornerProp)
	{
		if (!m_CornerProperties)
			m_CornerProperties = pCornerProp;
	}
}

void misCameraInteraction::Reset()
{
	m_Camera = 0;
	m_FocalPointCenter[0] = -1;
	m_FocalPointCenter[1] = -1;
	m_FocalPointCenter[2] = -1;

	m_PlaneCenter[0] = -1;
	m_PlaneCenter[1] = -1;
	m_PlaneCenter[2] = -1;
	m_CornerProperties = 0;
	m_CurrentZoomPercentage = 100;
	m_currentZoomProportion = 1;
}

zoomStrct misCameraInteraction::Reset2DZoom()
{
	SetCurrentZoomPercentage(100);
	SetCurrentZoomProportion(1);
	zoomStrct zoomStr;
	zoomStr.percentage = 100;
	zoomStr.proportion = 1;
	zoomStr.fromImageViewer = true;
	return zoomStr;
}