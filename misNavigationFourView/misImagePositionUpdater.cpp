#include "stdafx.h"
#include "misImagePositionUpdater.h"
#include "misVolumeSlicer.h"
#include "ICursorService.h"


misImagePositionUpdater::misImagePositionUpdater(std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> packeViewers,
	double virtaulTipExtend)
	:m_packageViewers(packeViewers), m_VirtaulTipExtend(virtaulTipExtend)
{
	
}

 
void misImagePositionUpdater::UpdatePosition(parcast::Point<double, 3> position)
{
	for (auto packageViewer : m_packageViewers)
	{
		packageViewer->UpdatePosition(position);
	}
}
 

 
void misImagePositionUpdater::SetVirtualTipExtend(double lenght)
{
	throw std::logic_error("The method or operation is not implemented.");
}
