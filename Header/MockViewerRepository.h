
#pragma once

#include "IViewerRepository.h"

MOCK_BASE_CLASS(MockViewerRepository, IViewerRepository)
{
	MOCK_NON_CONST_METHOD(FindViewer, 1, std::vector<std::shared_ptr<IVolumeRenderer>>(HWND window), FindViewer_1);
	MOCK_NON_CONST_METHOD(FindVolumeSlicer, 1, std::vector<std::shared_ptr<IVolumeSlicer>>(HWND window));
	MOCK_NON_CONST_METHOD(Find3DVolumeRenderer, 1, std::vector<std::shared_ptr<IVolume3DRenderer>>(HWND window));
	MOCK_CONST_METHOD(FindViewer, 3, std::vector<std::shared_ptr<IVolumeRenderer>>(HWND window, std::string sequenceName,
		std::string subsequnceName), FindViewer_2);
	MOCK_CONST_METHOD(GetImageViewers, 2, std::vector<std::shared_ptr<IVolumeRenderer>>(std::string sequenceName,
		std::string subsequnceName));
	MOCK_CONST_METHOD(GetVolumeSlicers, 2, std::vector<std::shared_ptr<IVolumeSlicer>>(std::string sequenceName,
		std::string subsequnceName));
	MOCK_CONST_METHOD(Get3dVolumeRenderer, 2, std::vector<std::shared_ptr<IVolume3DRenderer>>(std::string sequenceName,
		std::string subsequnceName));
	MOCK_CONST_METHOD(Get3DViewers, 2, std::vector<std::shared_ptr<I3DViewer>>(std::string sequenceName,
		std::string subsequnceName));
	MOCK_CONST_METHOD(GetAllViewers, 0, std::vector<std::shared_ptr<I3DViewer>>());
	MOCK_CONST_METHOD(GetAllImageViewers, 0, std::vector<std::shared_ptr<IVolumeRenderer>>());
	MOCK_NON_CONST_METHOD(FindMisWindow, 1, std::shared_ptr<Iwindows>(HWND window));
	MOCK_NON_CONST_METHOD(FindMisWindows, 2, std::vector<std::shared_ptr<Iwindows>>(std::string tabName, std::string subTabName));
	MOCK_NON_CONST_METHOD(GetAllWindow, 0, std::vector<std::shared_ptr<Iwindows>>());
	MOCK_NON_CONST_METHOD(FindActiveWindow, 0, std::shared_ptr<Iwindows>());
	MOCK_NON_CONST_METHOD(SetSequenceList, 1, void(const sequenceListTypdef& val));
};