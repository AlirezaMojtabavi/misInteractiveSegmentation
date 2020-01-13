#pragma once
#include "misCroppingDirectionInVR.h"
#include "misPackageViewingItemsStrct.h"
#include "misDataProdecureEnum.h"
#include "misPlanSTRCT.h"
#include "IPlanFlowUIAdapter.h"
#include "misPackageViewingItemsStrct.h"

class IBiopsyPlanningUIUpdater : public IPlanFlowUIAdapter
{
public:
	virtual void ChangeStatus(const std::string& statusString) = 0;
	virtual void Deactivated() = 0;
	virtual void UpdateZoomPercentage(int pZoomPercentage, double pZoomProportion) const = 0;
	virtual void UpdatePlanPropertyIndicatorValue(const misShort3DModelViewingStrct& indicatorVal) = 0;
	virtual void UpdateCompletetreeViewList(const PackageViewingListTypedef& packageList) = 0;
	virtual void ClearCompletetreeViewList() = 0;
	virtual void UpdatePackageList(const PackageViewingListTypedef& packageList) = 0;
	virtual void ClearPackageList() = 0;
	virtual void UpdatePlanColor(const misColorStruct& planColor) = 0;
};	
