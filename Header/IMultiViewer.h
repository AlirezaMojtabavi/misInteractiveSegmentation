#pragma once
#include "IVolumeRenderer.h"
#include "IVolumeSlicer.h"
class I3DViewer;
class IVolume3DRenderer;

class IMultiViewer
{
public:
	virtual std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() = 0;
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() = 0;
	virtual std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() = 0;
	virtual std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() = 0;

};
