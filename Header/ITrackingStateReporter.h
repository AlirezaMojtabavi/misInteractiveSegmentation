#pragma once

#include "misToolData.h"
#include "misTrackingManagerTypes.h"
#include "misTrackingToolStateReport.h"

// The ITrackingStateReporter class is the abstract interface for classes that can generate reports regarding current state of 
// a tracker and the tools under its control. These include information needed to warn user about using the tracker such as 
// interference, visibility, out of volume as well as other essentially useless statistical data in the form of a 
// misTrackingStateReport object. High level queries are also made possible using this interface.
class ITrackingStateReporter
{
public:
	// Updates internal statistical data and generates the tracking state report.
	virtual misTrackingStateReport GenerateReport() = 0;

	// Queries the underlying repository and gets whether any tool with the specified application flag is currently visible.
	virtual bool IsToolWithApplicationVisible(misToolProperties::ApplicationFlag flag) const = 0;
	
	virtual ~ITrackingStateReporter() { }
};