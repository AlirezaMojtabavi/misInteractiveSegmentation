#include "stdafx.h"

#include "BiopsyToolRepresentationDecider.h"
#include "IVolume3DRenderer.h"
#include "IToolRepresentationDecider.h"

using namespace parcast;

BiopsyToolRepresentationDecider::BiopsyToolRepresentationDecider()
{

}

misToolRepresentationType BiopsyToolRepresentationDecider::GetToolRepType(std::shared_ptr<IVolumeRenderer> viewer)
{
	if (viewer->GetTypeDirection() == Viewer3DLandmark)
	{
		return BiopsySpatialObj3D;
	}
	return BiopsySpatialObj2D;
}
