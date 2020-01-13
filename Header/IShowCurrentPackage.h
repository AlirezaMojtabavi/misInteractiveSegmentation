#pragma once
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"

class IShowCurrentPackage
{
public :
	virtual ~IShowCurrentPackage() = default;
	virtual void Show(std::shared_ptr<INavigationViewersNView> groupViewer, std::shared_ptr<ISimpleDataPackage> package) = 0;
};
