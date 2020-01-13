#pragma once

#include "ITrackerConnectivity.h"
#include "mis3DViewer.h"
#include "misCoreEvents.h"
#include "misEnums.h"
#include "misStrctConnectOption.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingManagerTypes.h"
#include "misTypes.h"
#include "igstkAuroraTracker.h"

class misTrackingObserver;
// The class overide and extend behavior of igstk::AuroraTracker,
//for extend capabilties provide by igstk we changed igstk::NDITracker,igstk::tracker and added misAuroraTracker
//probably only misAuroraTracker can provide  all functionalities by overriding virtual functions
class   misAuroraTracker : public igstk::AuroraTracker
{
public:
	igstkStandardClassTraitsMacro(misAuroraTracker, igstk::AuroraTracker);
 	bool Connect(misStrctComConnectionOptions connecting);
	bool Reset();

protected:
	misAuroraTracker(void);
	virtual ~misAuroraTracker(void);
	
private:
		// wait until tracker is ready (if tracker have steady waiting time)
	bool WaitUntileWarmUp(double timeOut);
	std::shared_ptr<const ICoordinateSystem> GetCameraCoordinateSystem() const;
	misAuroraTracker(const Self&);		//purposely not implemented
	void operator=(const Self&);		//purposely not implemented
	misApplicationSetting*				            m_pAppSetting;
	igstk::SerialCommunication::Pointer             m_serialComm;
	std::shared_ptr<const ICoordinateSystem> m_CameraCoordSys;

};