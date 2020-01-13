#pragma  once

#include "misExtraToolInformation.h"
#include "misTrackingToolMarkerReport.h"

// The IPolarisTrackingToolMarkerReport class is the abstract interface for classes that can generate reports regarding current
// state of a tracker tool and show each marker visibility status.
class ITrackingToolMarkerReporter
{
public:
	// Updates internal statistical data and generates the tracking tool marker visibility state report.
	virtual misTrackingToolMarkerReport GenerateReport() = 0;

	virtual ~ITrackingToolMarkerReporter() { }
};