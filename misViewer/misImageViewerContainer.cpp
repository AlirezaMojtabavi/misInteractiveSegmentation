#include "stdafx.h"
#include "misImageViewerContainer.h"




std::shared_ptr<IVolumeSlicer> misImageViewerContainer::GetImageViewer() const
{
	return m_ImageViewer;
}

void misImageViewerContainer::SetImageViewer(std::shared_ptr<IVolumeSlicer> val)
{
	m_ImageViewer = val;
}
