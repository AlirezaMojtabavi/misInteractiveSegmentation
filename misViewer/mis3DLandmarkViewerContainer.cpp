#include "stdafx.h"

#include "misVolumeRendererContainer.h"

IVolume3DRenderer* misVolumeRendererContainer::GetViewer() const
{
	return m_Viewer;
}

void misVolumeRendererContainer::SetViewer(IVolume3DRenderer* val)
{
	m_Viewer = val;
}
