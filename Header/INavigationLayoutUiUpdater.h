#pragma once

class misWindowsLayout;

class INavigationLayoutUiUpdater
{

public:
	virtual ~INavigationLayoutUiUpdater() = default;
	virtual void UpdateLayout(const misWindowsLayout&) = 0;
	virtual void ClearLayout() = 0;


};
