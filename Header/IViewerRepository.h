#pragma once

#include "mis3DViewer.h"
#include "IVolume3DRenderer.h"
#include "ISequenceManager.h"
#include "IVolumeSlicer.h"

// The IViewerRepository class search for viewers by name and  windows handle or both
class IViewerRepository
{
public:
	// Find viewer created from provided window handle
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> FindViewer(HWND window) = 0;
	virtual std::vector<std::shared_ptr<IVolumeSlicer>> FindVolumeSlicer(HWND window) = 0;
	virtual std::vector<std::shared_ptr<IVolume3DRenderer>> Find3DVolumeRenderer(HWND window) = 0;

	// Find viewer created from provided window handle, tab name and sub tab name 
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> FindViewer(HWND window, std::string sequenceName,
	                                                                   std::string subsequnceName) const = 0;
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> GetImageViewers(std::string sequenceName,
	                                                                std::string subsequnceName) const = 0;
	virtual std::vector<std::shared_ptr<IVolumeSlicer>> GetVolumeSlicers(std::string sequenceName,
		std::string subsequnceName) const = 0;
	virtual std::vector<std::shared_ptr<IVolume3DRenderer>> Get3dVolumeRenderer(std::string sequenceName,
		std::string subsequnceName) const = 0;

	virtual std::vector<std::shared_ptr<I3DViewer>> Get3DViewers(std::string sequenceName,
	                                                             std::string subsequnceName) const = 0;
	virtual std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() const = 0;
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() const = 0;
	virtual std::shared_ptr<Iwindows> FindMisWindow(HWND window) = 0;
	virtual std::vector<std::shared_ptr<Iwindows>> FindMisWindows(std::string tabName, std::string subTabName) =0;
	virtual std::vector<std::shared_ptr<Iwindows>> GetAllWindow() = 0;
	virtual std::shared_ptr<Iwindows> FindActiveWindow() = 0;
	virtual void SetSequenceList(const sequenceListTypdef& val) = 0;

	virtual ~IViewerRepository()
	{
	}
};
