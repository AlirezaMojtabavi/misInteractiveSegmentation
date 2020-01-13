#pragma once
class IGroupViewerSetting;

class INavigationLayoutFactory
{
public:

	virtual std::shared_ptr<IGroupViewerSetting> GetLayout() const = 0;
	virtual std::shared_ptr<IGroupViewerSetting> GetLayoutFromFile(const std::string& file)  const = 0;
};

