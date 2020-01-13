#pragma once

#include "ITracker.h"
#include <igstkTracker.h>
#include "misPolarisTracker.h"



class misPolarisTrackerWrapper : public ITracker
{
public:

	misPolarisTrackerWrapper(igstk::PolarisTracker* tracker);

	virtual bool InterferenceExists() const override;
	virtual std::string GetUID() const;
	virtual bool StopTracking() override;
	virtual bool StartTracking() override;
	void RemoveAllObservers() override;

	virtual void SetUID(std::string uid) override;


	virtual bool HasObserver(const itk::EventObject & event) const override;


	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *) override;


	virtual unsigned long AddObservers(const std::vector<itk::EventObject *>& events, itk::Command *) override;


	virtual bool Connect(misStrctComConnectionOptions connecting) override;


	virtual bool Reset() override;


	virtual void InvokeEvent(const itk::EventObject& event) override;


	virtual bool AddToolToTracker(std::shared_ptr<ITrackingTool> tool) override;


	virtual igstk::Tracker* GetTracker() override;


	virtual bool Close() override;

protected:
	igstk::PolarisTracker::Pointer m_Tracker;

private:
	void PolarisInterferenceObserver(itk::Object *caller, const itk::EventObject& event);
	bool m_InterferenceExists;
};

