#pragma once
#include "ITrackingTooolVisibiltyReport.h"

MOCK_BASE_CLASS(MockTrackingTooolVisibiltyReport, ITrackingTooolVisibiltyReport)
{
	MOCK_NON_CONST_METHOD(RefrenceAndNavigationToolAreVisible,0, bool());

	MOCK_NON_CONST_METHOD(GetAppropriateToolMarkerVisibilityReport, 0, misTrackingToolMarkerReport(void));
	MOCK_NON_CONST_METHOD(GetToolStateReport, 0, misTrackingStateReport());
	MOCK_NON_CONST_METHOD(IsToolWithApplicationVisible, 1, bool(misToolProperties::ApplicationFlag));
};
