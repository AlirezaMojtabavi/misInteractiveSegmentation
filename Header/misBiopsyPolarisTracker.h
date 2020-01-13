#pragma once

#include "mis3DViewer.h"
#include "misCoreEvents.h"
#include "misStrctConnectOption.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingManagerTypes.h"
#include "igstkPolarisTracker.h"
#include "IBiopsyToolDetector.h"
#include "IBiopsyToolDirFinder.h"
#include "IBiopsyToolTransformCalculatorTracker.h"

class misTrackingObserver;

// The class overide and extend behavior of igstk::PolarisTracker ,Ilumination rate , intefernce,..
//for extend capabilties provide by igstk we changed igstk::NDITracker,igstk::tracker and added misBiopsyPolarisTracker
//probably only misBiopsyPolarisTracker can provide  all functionalities by overriding virtual functions
class misBiopsyPolarisTracker : public igstk::PolarisTracker
{
public:

#pragma warning (push)
#pragma warning (disable : 4800)
	igstkLoadedEventMacro(misInterference, misEvent, bool);
#pragma warning (pop)
	void SetBiopsyToolDetector(std::shared_ptr<parcast::IBiopsyToolDetector> trackerTool);
	void SetBiopsyToolTransformCalculator(std::shared_ptr<parcast::IBiopsyToolTransformCalculatorTracker> toolTransformCalculator);
	typedef misBiopsyPolarisTracker Self;
	typedef itk::SmartPointer<Self> Pointer;
	typedef misLogger LoggerType;
	static Pointer New(void);
misSetMacro(UpdateOn, bool);
misGetMacro(UpdateOn, bool);
misSetMacro(IlluminationRate, int);
misGetMacro(IlluminationRate, int);
	bool RequestLaserOn(void);
	bool RequestLaserOff(void);
	bool RequestLaserStatus(bool status);
	void SetLogger(LoggerType* logger); //-M.A-Remains here unchanged
	bool Connect(misStrctComConnectionOptions connecting) override;
	bool Reset();

	std::shared_ptr<const ICoordinateSystem> GetCameraCoordinateSystem() const override;
	ResultType VerifyTrackerToolInformation(const TrackerToolType *) override;

protected:
	misBiopsyPolarisTracker(void);
	virtual ~misBiopsyPolarisTracker(void);
	/** Update the status and the transforms for all TrackerTools. add extra event like interferences that NDI dos not reports*/
	virtual ResultType InternalUpdateStatus(void);
	misLogger* GetLogger() const { return m_Logger; }
	igstk::Tracker::ResultType InternalThreadedUpdateStatus() override;

private:

	misBiopsyPolarisTracker(const Self&); //purposely not implemented
	void UpdateBiopsyToolTransform();

	void operator=(const Self&); //purposely not implemented
	mutable LoggerType* m_Logger;
	misStructPivotData m_pivotResult;
	misApplicationSetting* m_pAppSetting;


	igstk::SerialCommunication::Pointer m_serialComm;
	int m_IlluminationRate;
	int m_Volume;
	bool m_UpdateOn; //-M.A- not used
	itk::SmartPointer<misTrackingObserver> m_TrackerObserver;
	std::shared_ptr<const ICoordinateSystem> m_CameraCoordSys;
	std::shared_ptr<parcast::IBiopsyToolDetector> m_BiopsyToolDetector;
	std::shared_ptr<parcast::IBiopsyToolTransformCalculatorTracker> m_BiopsyToolTransformCalculator;
};
