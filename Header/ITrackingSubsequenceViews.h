#pragma once
#include "misGUIEvent.h"
#include "ITrackingTool.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingSequenceHelper.h"

// The ITrackingSubsequenceViews class rpresent mangeing and configiong a tracker with four view(dront, side, top, 3D)
class ITrackingSubsequenceViews
{
public:
	// Connect to tracker
	virtual bool ConnectToTracker() = 0;
	virtual void UpdateXYZView() = 0;
	virtual void UpdateTopView(double * bound) = 0;
	virtual void UpdateSideView(double * bound) = 0;
	virtual void UpdateFrontView(double * bound) = 0;
	virtual void UpdateStatus(long long int puls) = 0;
	virtual void UpdateViewOnCalibration() = 0;
	virtual void AddTrackerTool(std::shared_ptr<ITrackingTool>  pTracker) = 0;
	virtual std::shared_ptr<misSurfaceRepresentation> CameraObject(std::string fileName)  = 0;
	virtual bool ProcessRequest(misGUIEvent* pEvent) = 0;
	virtual void ResetSetting() = 0;
	virtual std::shared_ptr<misTrackingSequenceHelper> GetTrackerHelper() const = 0;

	///** Call Execute on all the Commands observing this event id. */
	//virtual void Invoke(const EventObject &) = 0;


};
