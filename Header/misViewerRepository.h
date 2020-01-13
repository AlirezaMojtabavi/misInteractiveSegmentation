#pragma once
#include "IViewerRepository.h"
#include "ISequenceManager.h"

class misViewerRepository : public IViewerRepository
{
public:
	misViewerRepository(sequenceListTypdef  sequenceList);
	misViewerRepository();

	std::vector<std::shared_ptr<IVolumeRenderer>> FindViewer(HWND window) override;
	std::vector<std::shared_ptr<IVolumeRenderer>> FindViewer(HWND window, std::string sequenceName, std::string subsequnceName) const override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetImageViewers(std::string sequenceName, std::string subsequnceName) const override;
	std::vector<std::shared_ptr<I3DViewer>> Get3DViewers(std::string sequenceName, std::string subsequnceName) const override;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() const override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() const override;
	std::shared_ptr<Iwindows> FindMisWindow(HWND window) override;
	std::vector<std::shared_ptr<Iwindows>> FindMisWindows(std::string tabName, std::string subTabName) override;
	std::vector<std::shared_ptr<Iwindows>> GetAllWindow() override;
	std::shared_ptr<Iwindows> FindActiveWindow();

	void SetSequenceList(const sequenceListTypdef& val) override;
	std::vector<std::shared_ptr<IVolumeSlicer>> FindVolumeSlicer(HWND window) override;
	std::vector<std::shared_ptr<IVolumeSlicer>> GetVolumeSlicers(std::string sequenceName,
		std::string subsequnceName) const override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> Find3DVolumeRenderer(HWND window) override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> Get3dVolumeRenderer(std::string sequenceName,
		std::string subsequnceName) const override;
private:
	sequenceListTypdef  m_SequenceList;

};

