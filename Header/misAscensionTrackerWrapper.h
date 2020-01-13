#pragma once

#include "ITracker.h"
#include "misAscensionTracker.h"

class misAscensionTrackerWrapper : public ITracker
{
public:
	misAscensionTrackerWrapper(misAscensionTracker::Pointer tracker);

	virtual std::string GetUID() const;
	bool StopTracking() override;
	bool StartTracking() override;
	void RemoveAllObservers() override;
	void SetUID(std::string uid) override;
	bool HasObserver(const itk::EventObject & event) const override;
	unsigned long AddObserver(const itk::EventObject & event, itk::Command *) override;
	unsigned long AddObservers(const std::vector<itk::EventObject *>& events, itk::Command *) override;
	bool Connect(misStrctComConnectionOptions connecting) override;
	bool Reset() override;
	void InvokeEvent(const itk::EventObject& event) override;
	bool AddToolToTracker(std::shared_ptr<ITrackingTool> tool) override;
	igstk::Tracker* GetTracker() override;
	bool InterferenceExists() const override;
	bool Close() override;

private:
	misAscensionTracker::Pointer m_Tracker;
};