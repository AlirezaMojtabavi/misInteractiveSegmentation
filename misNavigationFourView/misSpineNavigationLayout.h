#pragma once
#include "INavigationLayoutFactory.h"
class misSpineNavigationLayout :
	public INavigationLayoutFactory
{
public:
	misSpineNavigationLayout();
	~misSpineNavigationLayout();

	virtual std::shared_ptr<IGroupViewerSetting> GetLayout() const override;


	virtual std::shared_ptr<IGroupViewerSetting> GetLayoutFromFile(const std::string& layoutType) const override;

};

