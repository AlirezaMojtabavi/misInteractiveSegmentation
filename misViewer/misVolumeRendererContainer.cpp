#include "stdafx.h"

#include "misVolumeRendererContainer.h"

IVolumeRenderer* misVolumeRendererContainer::GetViewer() const
{
	return m_Viewer;
}

void misVolumeRendererContainer::SetViewer(IVolumeRenderer* val)
{
	m_Viewer = val;
}
