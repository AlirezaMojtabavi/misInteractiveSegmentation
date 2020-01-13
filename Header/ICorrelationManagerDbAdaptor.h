#pragma once
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystem.h"

// The ICorrelationManagerDbAdaptor saves and loads correlations to/from Db or any other persistent storage such as XML files 
// It acts as an adapter between a persistence storage and a working correlation manager.
class ICorrelationManagerDbAdaptor
{
public:
	// save transform results between source and destination coordinate with provided ids- deletes all existing correlation
	// from storage
	virtual void SaveCorrelationResults(const std::string& solutionUID) = 0;

	//load transform result between source and destination coordinate with provided ids
	virtual void LoadCorrelationResult(const std::string& solutionUID) = 0;
	
	// ICoordinateSystemCorrelationManager use to update correlation transforms when previously saved correlation read
	virtual void SetCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val) = 0;
	
};
