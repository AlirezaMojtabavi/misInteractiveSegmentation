#pragma once

#include "ISettingStorageEditor.h"
#include "ITrackerFilterSelector.h"
#include "ITrackingToolRepository.h"

namespace parcast
{

	class TrackerFilterSelector : public ITrackerFilterSelector
	{
	public:
		TrackerFilterSelector(
			const std::string& settingsFilePath, const std::string& filterSettingsRootNode, 
			std::shared_ptr<ISettingStorageEditor> settingsStorageEditor,
			std::shared_ptr<ITrackingToolRepository> toolRepo, int defaultKernelLength);

		void Default() override;
		void Select(int filterIndex) override;
		void RefreshFilters() override;
		int GetNumberOfFilters() const override;

	private:
		struct FilterData
		{
			std::string Name;
			std::vector<double> Coefficients;
		};

		const std::string SettingsFilePath;
		const std::string FilterSettingsRootNode;
		const int DefaultKernelLength;

		std::shared_ptr<ISettingStorageEditor> m_StorageEditor;
		std::shared_ptr<ITrackingToolRepository> m_ToolRepo;
		
		std::vector<FilterData> m_Filters;
	};

}
