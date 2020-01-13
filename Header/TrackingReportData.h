#pragma once

#include "misTrackingStateReport.h"
#include "misTrackingToolMarkerReport.h"

// The  TrackingReportData contains both tracking state information and and information of marker visibility
// (implemented only for polaris)
struct TrackingReportData
{
	misTrackingStateReport trackingReport;
	misTrackingToolMarkerReport toolReport;
};