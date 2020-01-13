#pragma once

#include "IViewerRepository.h"

namespace parcast
{

	class ViewerRepository : public IViewerRepository
	{
	public:
		ViewerRepository(const std::vector<mis3DViewer*>& viewersList);
		~ViewerRepository();

		// Find viewer created from provided window handle
		virtual std::vector<mis3DViewer*> FindViewer(HWND window) override;

		// Find all viewer created from  tab name and sub tab name
		virtual std::vector<mis3DViewer*> GetViewers(std::string sequenceName, std::string subsequnceName) const override;

		// Find viewer created from provided window handle, tab name and sub tab name 
		virtual std::vector<mis3DViewer*> FindViewer(HWND window, std::string sequenceName, std::string subsequnceName) const override;

	private:
		std::vector<mis3DViewer*> m_ViewersList;
	};

}