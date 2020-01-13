#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ITrackingToolQuery.h"
#include "ITrackingToolRepository.h"

// The misTrackingToolQuery provides a concrete implementation ITrackingToolQuery. It uses a ITrackingToolRepository as the 
// source of tools to perform query on. Each query is performed by applying the specified criteria to the tools in the 
// repository. If the query results in more than one tracking tool, it selects the tool according to correlation status of 
// each of the tools with a reference coordinate system. Still, if there are more than one tracking tools available with the
// correlation status, most recently observed tracking tool is selected. By default priority of correlation states is 
// Valid -> Invalid -> NoCorrelation. The default priority can be altered through SetCorrelationStatusPriorities.
// It also uses a ICoordinateSystemCorrelationManager according to which it determines correlation status of each tracking 
// tool with the reference coordinate system. The reference coordinate system will typically be the tracker coordinating 
// the tracking tool and the correlation states specify whether the tool is currently visible to the tracker, 
// currently invisible but observed before, or never observed before.
class misTrackingToolQuery : public ITrackingToolQuery
{
public:
	typedef  ICoordinateSystemCorrelationManager<std::string>  CorrelationManager;
	typedef std::vector<IComputedCorrelation::Status> CorrelationStatusPriorityList;

	// Creates a misTrackingToolQuery object specifying the source tracking tool repository, the correlation manager, and 
	// the UID of the reference coordinate system.
	misTrackingToolQuery(std::shared_ptr<ITrackingToolRepository> toolRepository, 
		std::shared_ptr<CorrelationManager> correlationManager, 
		const CorrelationManager::CoordinateSystemType &referenceCoordinateSystemUid);
	
	void SetCorrelationStatusPriorities(const CorrelationStatusPriorityList &priorities);

	virtual std::shared_ptr<ITrackingTool> ByApplicationFlag(misToolProperties::ApplicationFlag flag) const;

	virtual std::shared_ptr<ITrackingTool> ByPartNumber(const std::string& partNumber) const;

	virtual std::shared_ptr<ITrackingTool> ByToolName( const std::string& toolName ) const;

	// Gets the first tracking tool within the repository with the matching coordinate system UID and correlation status.
	virtual std::shared_ptr<ITrackingTool> ByUid(const std::string& uid) const;

	std::vector<std::shared_ptr<ITrackingTool>> GetAllVisibleCalibratedNavigationTools() const override;

	std::vector<std::shared_ptr<ITrackingTool>> GetAllVisibleCalibrationTools() const override;

private:
	// Gets the first tracking tool within the repository matching the criteria (the criteria function returns true given the
	// matching tracking tool) and according to the predefined correlation status priority.
	std::shared_ptr<ITrackingTool> ByCriteriaFunction(std::function<bool (std::shared_ptr<ITrackingTool>)> criteria) const;

	// Gets the first tracking tool within the repository matching the criteria (the criteria function returns true given the
	// matching tracking tool) and correlation status.
	std::shared_ptr<ITrackingTool> ByCriteriaFunctionAndCorrelationStatus(
		const ITrackingToolRepository::TrackerToolListType& toolsList, 
		std::function<bool (std::shared_ptr<ITrackingTool>)> criteria, IComputedCorrelation::Status correlationStatus) const;

	std::shared_ptr<ITrackingToolRepository> m_ToolRepository;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::string m_ReferenceCoordinateSystemUid;
	std::vector<IComputedCorrelation::Status> m_CorrelationStatusPriorities;
};  