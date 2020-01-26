#include "stdafx.h"
#include "..\Header\misVolumeRenderer.h"
#include "misLandmarkPointerRepresentation.h"
#include "misApplicationSetting.h"


misVolumeRenderer::misVolumeRenderer(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<Iwindows> pWindow, int index)
	: m_ROIBox(vtkSmartPointer<misROIWidget>::New()),
	m_IsROIActive(false),
	m_3DViewer(viewer),
	m_IsPointSelectObserverAdded(false)

{

	m_Renderer = m_3DViewer->GetRenderer();
	m_ViewPort = viewer->GetViewPort();
	m_IndexInGroup = viewer->GetIndexInGroup();
	m_CoordinateRenderers = viewer->GetCoordinateRenderers();
	m_SettingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
}

misVolumeRenderer::~misVolumeRenderer()
{
}

void misVolumeRenderer::ResetROI()
{
	m_IsROIActive = false;
	if (m_ROIBox)
		m_ROIBox->Off();
}
vtkRenderWindowInteractor* misVolumeRenderer::GetRendererWindowInteractor()
{
	return m_3DViewer->GetWindow()->GetInterActor();
}
void misVolumeRenderer::AddAllPointSelectObserve()
{
	for (auto obserevrElement : m_Observers)
	{
		if (!m_IsPointSelectObserverAdded)
		{
			for (auto vtkObserver : obserevrElement.second)
			{
				GetRendererWindowInteractor()->AddObserver(obserevrElement.first, vtkObserver);
			}
		}
	}
}
void misVolumeRenderer::AddPointSelectObserver(std::pair<unsigned long, vtkSmartPointer<vtkCommand>> observer)
{
	m_Observers[observer.first].push_back(observer.second);
}