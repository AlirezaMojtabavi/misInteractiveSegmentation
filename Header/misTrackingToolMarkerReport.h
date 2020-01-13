#pragma once

#include "misExtraToolInformation.h"
#include "misToolProperties.h"

// The misTrackingToolMarkerReport contains markers visibility status and an image that visually shows the invisible markers.
struct misTrackingToolMarkerReport
{
	std::string m_ToolName;
	// Markers visibility information
	misExtraToolInformation toolinfo;
	misToolProperties::ApplicationFlag toolType;
	// Windows handle of generated bitmap
	HBITMAP toolImage;
};
