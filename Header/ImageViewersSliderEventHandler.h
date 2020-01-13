#pragma once
#include "misReversibleValue.h"
#include "misAuroraTrackerWrapper.h"
class misSliderEvent;
class misGUIEvent;
class IViewerRepository;

class ImageViewersSliderEventHandler
{
public:

	ImageViewersSliderEventHandler(std::weak_ptr<IViewerRepository> viewerRepo) :
		m_SettingPositionBySliceNumber(false),
		m_ViewerRepo(viewerRepo)
	{
	}

	bool m_SettingPositionBySliceNumber;

	void UpdateSliders(misGUIEvent* guiEv);

private:
	std::weak_ptr<IViewerRepository> m_ViewerRepo;
};
