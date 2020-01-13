#include "stdafx.h"

#include "ToolRepresentationDecider.h"
#include "IVolume3DRenderer.h"
#include "IToolRepresentationDecider.h"

using namespace parcast;

parcast::ToolRepresentationDecider::ToolRepresentationDecider()
{

}

misToolRepresentationType ToolRepresentationDecider::GetToolRepType(std::shared_ptr<IVolumeRenderer> viewer)
{
	auto typeDirection = viewer->GetTypeDirection();
	if (typeDirection == Viewer3DLandmark)
	{
		return RealModel3D;
	}
	else if (typeDirection == AxialDirection || typeDirection == CoronalDirection || typeDirection == SagittalDirection ||
		typeDirection == PanormaicView)
	{
		return SpatialObj2D;
	}
	return {};
}
