#include "stdafx.h"
#include "..\Header\UpdatePlaneVisibilitiy.h"
#include "misVisibiltyHolder.h"


UpdatePlaneVisibilitiy::UpdatePlaneVisibilitiy(std::shared_ptr<IVolumeSlicer> volumeSlicer,
	std::shared_ptr<IVisibiltyHolder> visibiltyHolder) : m_2DViewer(
		volumeSlicer), m_VisibiltyHolder(visibiltyHolder)
{
}

void UpdatePlaneVisibilitiy::UpdatePlaneVisibilities(const std::map<misPlaneEnum, bool>  imageVisibiltes,
	std::map<misPlaneEnum, bool> pPlaneVisible)
{
	auto Gpu2DRep = m_2DViewer->GetImageRprensentaion();
	if (Gpu2DRep)
	{
		Gpu2DRep->SetDefautltVisibiltyPlanesMap(m_VisibiltyHolder);
		Gpu2DRep->ApplyDefaultVisibilityMap(imageVisibiltes);
	}

}

 