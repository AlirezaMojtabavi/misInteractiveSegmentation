#pragma once

#include "ITrackingToolMarkerReporter.h"
#include "ITrackingTool.h"
#include "misToolImageBlender.h"
#include "misTrackingToolMarkerReport.h"

// The implementation class of IPolarisTrackingToolMarkerReport interface 
class misTrackingToolMarkerReporter : public ITrackingToolMarkerReporter
{
public:
	misTrackingToolMarkerReporter(std::shared_ptr<const ITrackingTool> tool);
	
	virtual misTrackingToolMarkerReport GenerateReport();

private:
	// Returns information needed to report tool visibility marker states
	misExtraToolInformation ConvertExtraToolInformation( ToolExtraInformation toolInfo , int numberOfMarkers);
	
	// Loads and creates the image that visually show markers status.
	HBITMAP GetToolImage( misExtraToolInformation extraToolInfo , misToolImageStrct imageData);
	
	std::shared_ptr<const ITrackingTool> m_Tool;

	// Don't play smart to make this member a local variable. It must be created only once during the lifetime of this object.
	misToolImageBlneder m_ToolImageBelender;

};

