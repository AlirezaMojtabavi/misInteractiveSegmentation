#pragma once

#include "misGuiStructures.h"
#include "misPackageViewingItemsStrct.h"
#include "misPlanSTRCT.h"

// The IPlanningHelperUIUpdater class is the abstract interface held by misPlanningHelper objects and used to emit events to the
// superordinate (GUI) environment.
class IPlanningHelperUIUpdater
{
public:
	virtual ~IPlanningHelperUIUpdater(void) = default;

	virtual void UpdateImageAnd3DModelProperties(const misImageAnd3DModelPropertiesSettingStrct& currentProp) = 0;
	virtual void UpdatePlanPropertyIndicatorValue(const ScrewPlanPropertyIndicator& indicatorVal) = 0;
	virtual void UpdatePackageList(const PackageViewingListTypedef& packageList) = 0;
	virtual void ClearPackageList() = 0;
	virtual void ChangeStatus(const std::string& statusString) = 0;
	virtual void UpdateZoomPercentage(int percentage , double proportion) = 0;
	virtual void Deactivated() = 0;
	virtual void UpdateCutDirectionButtons(misCroppingDirectionInVR croppingDirection) = 0;
	virtual  void UpdateCompletetreeViewList(const PackageViewingListTypedef& packageList) = 0;
	virtual void ClearCompletetreeViewList() = 0;


};

