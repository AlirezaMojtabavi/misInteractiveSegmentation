#pragma once
#include "misStrctConnectOption.h"
#include "ITrackingTool.h"
#include "misSmoothingDeciderFactory.h"

struct misStrctSimpleToolProperties;

class ITrackerConfigure
{
public:
	virtual void DeleteTool(misStrctSimpleToolProperties ToolPropFromGui) = 0;
	virtual void AddObserversAddTools(misToolPropertiesListTypdef ListOfTools) = 0;
	virtual void MakeAndSendAddEvent(std::shared_ptr<ITrackingTool> ms) = 0;
	virtual std::vector<std::shared_ptr<ITrackingTool>> AddToolList(misToolPropertiesListTypdef ToolList) = 0;
	virtual std::shared_ptr<ITrackingTool> MakeTool(misToolProperties data) = 0;
	virtual void CheckTrackerConnectivity() = 0;
	virtual bool ResetTracker() = 0;
	virtual void CloseTracker() = 0;
	virtual bool Connect(misStrctComConnectionOptions connecting) = 0;
	virtual igstk::Tracker* GetTracker() = 0;
	virtual void SetConnectionFailureFlag(bool flag) = 0;
	virtual bool GetConnectionFailureFlag()  = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *) = 0;
	virtual bool GetTrackerDisconnected() const = 0;
	virtual void SetSmoothingDecider(std::shared_ptr<misSmoothingDeciderAbstarctFactory> val) = 0;
};