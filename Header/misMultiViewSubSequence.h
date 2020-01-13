#pragma once

#include "misSubSequence.h"
#include "IMultiViewer.h"

class ISimpleDataPackage;
class INavigationViewersNView;
class misApplicationSetting;

class misMultiViewSubSequence : public misSubSequence, public IMultiViewer
{
public:
	misMultiViewSubSequence(std::shared_ptr<misSoftwareInformation> softwareInformation);
	virtual std::weak_ptr<INavigationViewersNView> GetGroupViewer() = 0;
	virtual ~misMultiViewSubSequence(void) = default;
	void UpdateZoomPercentage(int percentage, double proportion);
};