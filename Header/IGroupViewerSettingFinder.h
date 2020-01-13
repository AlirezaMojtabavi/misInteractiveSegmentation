#pragma once
class IGroupViewerSetting;

class IGroupViewerSettingFinder
{
public:
	virtual std::shared_ptr<IGroupViewerSetting> MakePckageGroupViewer(std::string subTabName) = 0;
};
