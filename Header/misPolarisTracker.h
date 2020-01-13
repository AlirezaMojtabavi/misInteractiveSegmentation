#pragma once

#include "ITrackerConnectivity.h"
#include "mis3DViewer.h"
#include "misCoreEvents.h"
#include "misEnums.h"
#include "misStrctConnectOption.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingManagerTypes.h"
#include "misTypes.h"
#include <igstkPolarisTracker.h>

class misTrackingObserver;
// The class overide and extend behavior of igstk::PolarisTracker ,Ilumination rate , intefernce,..
//for extend capabilties provide by igstk we changed igstk::NDITracker,igstk::tracker and added misPolarisTracker
//probably only misPolarisTracker can provide  all functionalities by overriding virtual functions
class   misPolarisTracker : public igstk::PolarisTracker
{
public:

#pragma warning (push)
#pragma warning (disable : 4800)
	igstkLoadedEventMacro(misInterference, misEvent, bool);
#pragma warning (pop)
	
	typedef misPolarisTracker Self;
	typedef itk::SmartPointer<Self>	Pointer;
	typedef misLogger LoggerType;
	static  Pointer New(void); 
	misSetMacro(IlluminationRate, int);
	misGetMacro(IlluminationRate, int);
	bool RequestLaserOn(void);
	bool RequestLaserOff(void);
	bool RequestLaserStatus(bool status);
	void SetLogger(LoggerType *logger);//-M.A-Remains here unchanged
	bool Connect(misStrctComConnectionOptions connecting) override;
	bool Reset();

	virtual std::shared_ptr<const ICoordinateSystem> GetCameraCoordinateSystem() const override;

protected:
	misPolarisTracker(void);
	virtual ~misPolarisTracker(void);
	/** Update the status and the transforms for all TrackerTools. add extra event like interferences that NDI dos not reports*/
	virtual ResultType InternalUpdateStatus( void );
	misLogger* GetLogger() const { return m_Logger; }

private:
	
	misPolarisTracker(const Self&);		//purposely not implemented
	void operator=(const Self&);		//purposely not implemented
	mutable LoggerType* m_Logger;
	misStructPivotData	m_pivotResult;
	misApplicationSetting* m_pAppSetting;
	igstk::SerialCommunication::Pointer m_serialComm;
	int	m_IlluminationRate;
	int	m_Volume;
	itk::SmartPointer < misTrackingObserver >  m_TrackerObserver;
	std::shared_ptr<const ICoordinateSystem> m_CameraCoordSys;
 };