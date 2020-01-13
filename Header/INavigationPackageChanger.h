#pragma once
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"


class INavigationPackageChanger
{
public:
	virtual ~INavigationPackageChanger() = default;
	virtual void ChangePackage(std::shared_ptr<INavigationViewersNView> groupViewer, const std::string&  newPackgeUID, const std::string& selectedLayout,
	                           double VisibilityMarginInAnatomicalPlanesDirection, bool freezeState) = 0;
 };
