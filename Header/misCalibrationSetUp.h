#pragma once
#include "misToolPivotCalibration.h"

class  misCalibrationSetUp:public  misOldObject
{
private:
	// -------------
	// Tracking Parameters -----------------------------------------------------------------------
	//itk::SmartPointer<misPolarisTracker>	m_tracker;	//changed by -M.A-
	itk::SmartPointer<igstk::Tracker>	m_tracker;

	misToolData*							m_tool;

public:
	igstkStandardClassBasicTraitsMacro(misCalibrationSetUp,misOldObject);
	misToolPivotCalibration*		CalibrationWizard;
	unsigned int				numberOfFrames;
	unsigned int				delayInSeconds;

	misCalibrationSetUp(unsigned int FrameNum, unsigned int delayInSecs,
						igstk::Tracker::Pointer m_Tracker,
						misToolData* m_TrackerTool);
	~misCalibrationSetUp(void);
	virtual void InitializeTrackingAndCalibration();
	virtual void SaveCalibration();

	/** Add an observer so that an outside class is notified of events. */
	unsigned long AddObserver( const itk::EventObject & event,
		itk::Command *command );
	unsigned long AddObserver( const itk::EventObject & event,
		itk::Command *command ) const;
	void RemoveObserver( unsigned long observerID );

private:
	// -------------
	// Calibration Observers ---------------------------------------------------------------------
	//pivot calibration get transform observer
	igstkObserverMacro( TransformTo,
		igstk::CoordinateSystemTransformToEvent,
		igstk::CoordinateSystemTransformToResult )
		TransformToObserver::Pointer m_TransformToObserver;

	//pivot calibration get RMSE observer
	igstkObserverMacro( RMSE,
		igstk::DoubleTypeEvent,
		igstk::EventHelperType::DoubleType )
		RMSEObserver::Pointer m_RMSEObserver;

	//pivot calibration success/failure observer
	typedef itk::MemberCommand<misCalibrationSetUp>
		CalibrationSuccessFailureObserverType;
	void OnCalibrationSuccessFailureEvent( itk::Object *caller,
		const itk::EventObject & event );
	CalibrationSuccessFailureObserverType::Pointer m_CalibrationSuccessFailureObserver;

	//observer for write failure event
	typedef itk::MemberCommand<misCalibrationSetUp>
		WriteFailureObserverType;
	void OnWriteFailureEvent( itk::Object *caller,
		const itk::EventObject & event );

	//observer for write failure event
	typedef itk::MemberCommand<misCalibrationSetUp>   	ObserveCalibartionEventDataType;
	ObserveCalibartionEventDataType::Pointer   m_ObserveEventData;
	void ObserveCalibartionEventData( itk::Object *caller,
		const itk::EventObject & event );
};
