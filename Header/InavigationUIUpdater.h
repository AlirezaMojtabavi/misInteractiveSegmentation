#pragma once
#include "misCroppingDirectionInVR.h"
class INavigationUIUpdater
{
public:
	virtual ~INavigationUIUpdater() = default;
	virtual void UpdateZoomPercentage(int percentage, double proportion) = 0;
	virtual void UpdateViewTypes(std::vector<std::string> layouts) = 0;
	virtual void ClearPackageListTreeView() = 0;
	virtual void ShowSelectedPackage(const std::string& uid) = 0;
	virtual void ForceViewersToFreez(bool freezState) = 0;
	virtual void ShowPackageListInGUI() = 0;
	virtual void UpdateCroppingDirectionInGUI(misCroppingDirectionInVR cropping) = 0;

};
	