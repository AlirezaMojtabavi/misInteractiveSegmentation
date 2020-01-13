#pragma once

#include "ITrackingTool.h"
#include "misToolProperties.h"

// The ITrackingToolQuery class serves as an abstract interface for classes that perform queries on the contents of 
// a tracking tool repository. 
class ITrackingToolQuery
{
public:
	// Gets the first tracking tool within the repository with the matching application flag and correlation status.
	virtual std::shared_ptr<ITrackingTool> ByApplicationFlag(misToolProperties::ApplicationFlag flag) const = 0;

	// Gets the first tracking tool within the repository with the matching part number and correlation status.
	virtual std::shared_ptr<ITrackingTool> ByPartNumber(const std::string& partNumber) const = 0;

	// Gets the first tracking tool within the repository with the matching tool name and correlation status.
	virtual std::shared_ptr<ITrackingTool> ByToolName(const std::string& toolName) const = 0;

	// Gets the first tracking tool within the repository with the matching coordinate system UID and correlation status.
	virtual std::shared_ptr<ITrackingTool> ByUid(const std::string& uid) const = 0;

	//Gets all navigation tools that exist in scene.
	virtual std::vector<std::shared_ptr<ITrackingTool>> GetAllVisibleCalibratedNavigationTools() const = 0;

	//Gets all calibration tools that exist in scene.
	virtual std::vector<std::shared_ptr<ITrackingTool>> GetAllVisibleCalibrationTools() const = 0;

	// Gets The list of 
	virtual ~ITrackingToolQuery(void) { }
};

