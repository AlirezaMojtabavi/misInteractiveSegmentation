#pragma once
#include "igstkLogger.h"
#include "igstkPivotCalibration.h"
#include "igstkPolarisTracker.h"
#include "igstkPolarisTrackerTool.h"
#include "igstkPulseGenerator.h"
#include "itkCommand.h"
#include "igstkTransformObserver.h"
#include "itkFixedArray.h"
#include "misToolData.h"
#include "misApplicationSetting.h"
// The class expects the tracker to be in tracking state.
// Once initialized pressing the "Calibrate" button will start
// data acquisition (after a user set delay) and perform calibration.

class  misStrctToolPivotCalibrationData
{
public:
	double  x,y,z;
	std::string ToolRomFilesAddress;
	misToolData* pTool;
};

igstkLoadedEventMacro(misToolCalibrationEvent,misEvent,misStrctToolPivotCalibrationData);
class misToolPivotCalibration:public  misOldObject
{
private:
	misApplicationSetting*					m_pAppSetting;
public:
	igstkStandardClassBasicTraitsMacro(misToolPivotCalibration,misOldObject);
	misToolData*						m_Tool;
	typedef igstk::PivotCalibration		PivotCalibrationType;
	PivotCalibrationType::Pointer		m_PivotCalibration;

	double								RMSError;
	igstk::Transform::VectorType		Translation;
	igstk::EventHelperType::PointType	PivotPoint;
	igstk::Transform::VersorType		quaternionRotation;

	unsigned int delayInSeconds;
	unsigned int FrameNum;

	misToolPivotCalibration(){};
	misToolPivotCalibration(unsigned int n, unsigned int delayInSecs,
							misToolData* trackerTool);
	~misToolPivotCalibration(void);

	/** This method sets the number of transformations required for performing
   *  the pivot calibration, and the tool information.
   *  It is assumed that the tracker is already in tracking mode.
   *  If the initialization fails a message box will be displayed.
   *  The method generates two events: InitializationSuccessEvent and
   *  InitializationFailureEvent. */
  void RequestInitialize( unsigned int n, misToolData*	trackerTool );

  /** This method sets the delay in seconds between the moment the
   *  "Calibrate" button is pressed and the beginning of data acquisition. */
  void RequestSetDelay( unsigned int delayInSeconds );

  void RequestComputeCalibration();

  /** This method is used to request the calibration transformation.
   *  The method should only be invoked after a successful calibration.
   *  It generates two events: CoordinateSystemTransformToEvent, and
   *  TransformNotAvailableEvent, respectively denoting that a calibration
   *  transform is and isn't available. */
  void RequestCalibrationTransform();

  /** This method is used to request the pivot point, given in the coordinate
   *  system in which the user supplied transforms were given. It generates two
   *  events: PointEvent, and InvalidRequestErrorEvent, respectively denoting
   *  that the pivot point is and isn't available. */
  void RequestPivotPoint();

  /** This method is used to request the Root Mean Square Error (RMSE) of the
   *  overdetermined equation system used to perform pivot calibration. It
   *  generates two events: DoubleTypeEvent, and InvalidRequestErrorEvent,
   *  respectively denoting that the RMSE is and isn't available.
   *  \sa PivotCalibrationAlgorithm */
  void RequestCalibrationRMSE();

  /** Add an observer so that an outside class is notified of events. */
  unsigned long AddObserver( const itk::EventObject & event,
	  itk::Command *command );
  unsigned long AddObserver( const itk::EventObject & event,
	  itk::Command *command ) const;
  void RemoveObserver( unsigned long observerID );

private:
	unsigned int						m_delay;

	typedef igstk::Object::LoggerType	LoggerType;
	typedef itk::StdStreamLogOutput		LogOutputType;
	LoggerType::Pointer					m_Logger;
	LogOutputType::Pointer				m_LogOutput;
	std::ofstream						m_LogFile;
	LoggerType::Pointer					SetaLoggerforDEBUGLOGGINGing();

	//description of the tool we want to calibrate
	std::string							m_currentToolInformation;

	//accumulate the calibration information in this stream and
	//then display to the user
	std::ostringstream					m_calibrationInformationStream;

	// Define Observers -------------------------------------------------------
	//pivot calibration initialization observer
	typedef itk::MemberCommand<misToolPivotCalibration>
		InitializationObserverType;
	void OnInitializationEvent( itk::Object *caller,
		const itk::EventObject & event );
	InitializationObserverType::Pointer m_InitializationObserver;

	//pivot calibration events observer(start, progress, end) during Calibration
	typedef itk::MemberCommand<misToolPivotCalibration>
		CalibrationObserverType;
	void OnCalibrationEvent( itk::Object *caller,
		const itk::EventObject & event );
	CalibrationObserverType::Pointer m_CalibrationObserver;

	//pivot calibration get transform observer
	igstkObserverMacro( TransformTo,
		igstk::CoordinateSystemTransformToEvent,
		igstk::CoordinateSystemTransformToResult )
		TransformToObserver::Pointer m_TransformToObserver;

	//pivot calibration get pivot point observer
	igstkObserverMacro( PivotPoint,
		igstk::PointEvent,
		igstk::EventHelperType::PointType )
		PivotPointObserver::Pointer m_PivotPointObserver;

	//pivot calibration get RMSE observer
	igstkObserverMacro( RMSE,
		igstk::DoubleTypeEvent,
		igstk::EventHelperType::DoubleType )
		RMSEObserver::Pointer m_RMSEObserver;
};
