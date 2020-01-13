#pragma once

#include "IPlanningHelperUIUpdater.h"

MOCK_BASE_CLASS(MockPlanningHelperUIUpdater, IPlanningHelperUIUpdater)
{
	MOCK_NON_CONST_METHOD(UpdateImageAnd3DModelProperties, 1, void(const misImageAnd3DModelPropertiesSettingStrct& currentProp));
	MOCK_NON_CONST_METHOD(UpdatePlanPropertyIndicatorValue, 1, void(const ScrewPlanPropertyIndicator& indicatorVal));
	MOCK_NON_CONST_METHOD(UpdatePackageList, 1, void(const PackageViewingListTypedef& packageList));
	MOCK_NON_CONST_METHOD(ClearPackageList, 0, void());
	MOCK_NON_CONST_METHOD(ChangeStatus, 1, void(const std::string& statusString));
	MOCK_NON_CONST_METHOD(UpdateZoomPercentage, 2, void(int percentage, double proportion));
	MOCK_NON_CONST_METHOD(Deactivated, 0, void());
	MOCK_NON_CONST_METHOD(UpdateCutDirectionButtons, 1, void (misCroppingDirectionInVR ) );
	MOCK_NON_CONST_METHOD(UpdateCompletetreeViewList, 1, void(const PackageViewingListTypedef& ));
	MOCK_NON_CONST_METHOD(ClearCompletetreeViewList, 0,void());

};
