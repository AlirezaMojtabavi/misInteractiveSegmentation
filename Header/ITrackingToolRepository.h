#pragma once

#include "ITrackingTool.h"

// The ITrackingToolRepository class is the abstract interface for storage classes holding a collection of ITrackingTool objects.
class ITrackingToolRepository
{
public:
	typedef std::list<std::shared_ptr<ITrackingTool>> TrackerToolListType;

	// append tool to internal container
	virtual void AddTool(std::shared_ptr<ITrackingTool> newTool) = 0;

	// remove tool from internal container
	virtual void RemoveTool(std::shared_ptr<ITrackingTool> newTool) = 0;

	// Remove all tools from the internal container.
	virtual void RemoveAllTools() = 0;

	// Retrieve a list all the tracking tool objects stored within the repository.
	virtual TrackerToolListType GetAllTools() const = 0;

	virtual ~ITrackingToolRepository() {}
};