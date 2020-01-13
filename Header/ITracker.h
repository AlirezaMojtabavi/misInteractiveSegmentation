#pragma once
#include "misStrctConnectOption.h"
#include "misToolData.h"

class ITracker
{
public:
	virtual std::string GetUID() const = 0;
	virtual void SetUID(std::string uid) = 0;
	virtual bool StopTracking() = 0;//Returns true if stop succeed, false if stop failed.
	virtual bool StartTracking() = 0;
	/** Return true if an observer is registered for this event. */
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *) = 0;
	virtual unsigned long AddObservers(const std::vector< itk::EventObject*>& events, itk::Command *) = 0;
	virtual void RemoveAllObservers() = 0;
	virtual bool Connect(misStrctComConnectionOptions connecting) = 0;
	virtual bool Reset() = 0;
	virtual bool Close() = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual bool AddToolToTracker(std::shared_ptr<ITrackingTool> tool) = 0;
	virtual bool InterferenceExists() const = 0;
	virtual igstk::Tracker* GetTracker() = 0;
	virtual ~ITracker(){}
};
