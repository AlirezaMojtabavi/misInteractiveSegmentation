#pragma once

#include "misToolProperties.h"

struct misTrackingToolMarkerReport;
class misTrackingStateReport;

class ITrackingTooolVisibiltyReport
{
public:
	~ITrackingTooolVisibiltyReport() = default;

	virtual bool RefrenceAndNavigationToolAreVisible() = 0;
	virtual misTrackingToolMarkerReport GetAppropriateToolMarkerVisibilityReport() = 0;
	virtual misTrackingStateReport GetToolStateReport() = 0;
	virtual bool IsToolWithApplicationVisible(misToolProperties::ApplicationFlag flag) = 0;
};
