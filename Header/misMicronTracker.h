#pragma once


#include "mis3DViewer.h"
#include "misCoreEvents.h"
#include "misEnums.h"
#include "misMicronTrackerSetting.h"
#include "misStrctConnectOption.h"
#include "misSurfaceRepresentation.h"
#include "misThreadSafeValue.h"
#include "misTrackingManagerTypes.h"
#include "misTrackingObserver.h"
#include "misTypes.h"
#include "ITrackerConnectivity.h"
#include <igstkTracker.h>
#include "XPoints.h"

// MicronTracker utilitiy classes declarations.
// These classes are part of the MTC library
// and can be found in the Utilities subdirectory.
class misMicronTracker : public igstk::Tracker
{
public:	

	/** Typedef for internal boolean return type. */
	typedef Tracker::ResultType   ResultType;
	bool Reset();

	//Initializes Camera calibration and marker template directory of micron tracker. And always returns true
	void InitializeCameraConnectionParameters();
	bool SetCameraParameters();
	bool SetMarkerTemplateParam();
	bool OpenCommunication();
	bool CloseCommunication();
	bool Connect(/*std::string NameOfiniFile*/);
	bool EnableJitterFilter( JitterParameters jitter);
	bool StarttSucssed;
	void SetAutoCalculateLightCoolness(bool val);
	void SetCameraLightCoolness(double val);
	/** Macro with standard traits declarations. */
	igstkStandardClassTraitsMacro( misMicronTracker, Tracker )
		/** Get the number of tools that have been detected. */
	igstkGetMacro( NumberOfTools, unsigned int );
	/** Set the directory path that contains the camera calibration
	* files.
	*/
	igstkSetStringMacro( CameraCalibrationFilesDirectory );

	/** Set marker templates directory */
	igstkSetStringMacro( MarkerTemplatesDirectory );

	/** Print object information */
	virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const;

	/** Create an associative container that maps error code to error
	* descritpion */
	static void CreateErrorCodeList();

	/** Get Error description given the error code */
	static std::string GetErrorDescription( unsigned int );

	/** Remove tracker tool entry from internal containers */
	virtual ResultType RemoveTrackerToolFromInternalDataContainers( const
		TrackerToolType * trackerTool );

	/** Add tracker tool entry from internal containers */
	virtual ResultType AddTrackerToolToInternalDataContainers( const
		TrackerToolType * trackerTool );
	mtCompletionCode LogFileSet(bool value );
	//Create an associative container that maps Measurement hazard codes to error description
	static void CreateMeasurmentHazardCodeList();

	//gets the code and returns the string describing the measurement hazard.
	std::string GetMeasurementHazardDescription( unsigned int code );
	void SetLightCoolness(double Value);
	void ExitTrackingStateProcessing( void );
	bool HdrEnable(bool HdrEnableStatus);
	bool HistogramEqualizeImagesEnable(bool HistogramEqualizeEnableStatus);
	void AutoSetLightCoolness(MTMarker::Marker* CurrentMarker);


	virtual std::shared_ptr<const ICoordinateSystem> GetCameraCoordinateSystem() const;

	// specifies a list of prefixes, identified as name for reference
	void misMicronTracker::SetReferencePrefixList( const std::vector<std::string> & prefix );
	bool GetProcessXpoint() const;
	void SetProcessXpoint(bool val);
private:
	/** A buffer to hold tool transforms */
	typedef std::map< std::string, std::vector < double > > TrackerToolTransformContainerType;
	typedef ::itk::Versor<double> VersorType;
	typedef ::itk::Vector<double, 3> VectorType;
	typedef std::map< unsigned int, std::string>  ErrorCodeContainerType;
	typedef vnl_vector<double> PointType;
	misMicronTracker(const Self&);		//purposely not implemented not by -M.A-
	misMicronTracker(void);
	virtual ~misMicronTracker(void);
	void operator=(const Self&);   //purposely not implemented
	/** Initialize camera and algorithm attributes such as Frame interleave
	template matching tolerance, extrapolate frame etc */
	//bool Initialize();
	/** load marker templates */
	bool LoadMarkerTemplates();
	/** Setup cameras */
	bool SetUpCameras();
	/** Open communication with the tracking device. */
	virtual ResultType InternalOpen( void );

	/** Close communication with the tracking device. */
	virtual ResultType InternalClose( void );

	/** Put the tracking device into tracking mode. */
	virtual ResultType InternalStartTracking( void );

	/** Take the tracking device out of tracking mode. */
	virtual ResultType InternalStopTracking( void );

	/** Update the status and the transforms for all TrackerTools. */
	virtual ResultType InternalUpdateStatus( void );

	void UpdateCameraImages();

	/** Update the status and the transforms.
	This function is called by a separate thread. */
	virtual ResultType InternalThreadedUpdateStatus( void );

	mtHandle SetGlobalReference( Collection* markersCollection );

	// searches the marker collection for reference
	mtHandle SearchForReference( Collection* markersCollection );

	/** Reset the tracking device to put it back to its original state. */
	virtual ResultType InternalReset( void );

	/** Verify tracker tool information */
	virtual ResultType VerifyTrackerToolInformation( const TrackerToolType * );

	/** The "ValidateSpecifiedFrequency" method checks if the specified  
	*  frequency is valid for the tracking device that is being used. */
	virtual ResultType ValidateSpecifiedFrequency( double frequencyInHz );

	// Converts the specified Micron transform to its IGSTK transform equivalent
	igstk::Transform CreateIgstkTransform(Xform3D* micronTransform, double error, double validityPeriod);

	// (De)serializes a IGSTK transform to/from a std::vector of double precision float values such that the first three elements of
	// the vector are Cartesian components of translation, the next three elements specify the rotation axis, and the last element
	// is the rotation angle.
	std::vector<double> SerializeIgstkTransform(const igstk::Transform& trans);
	igstk::Transform DeserializeIgstkTransform(const std::vector<double>& serializedTrans);

	/** A mutex for multithreaded access to the buffer arrays */
	itk::MutexLock::Pointer m_BufferLock;

	misThreadSafeValue<igstk::Transform> m_CameraTransform;

	std::shared_ptr<const ICoordinateSystem> m_CameraCoordSys;

	/** Total number of tools detected. */	
	unsigned int   m_NumberOfTools;

	/** Calibration files directory */
	std::string m_CameraCalibrationFilesDirectory;

	/** marker template directory */
	std::string m_MarkerTemplatesDirectory;

	//Persistence * m_Persistence;
	Markers     * m_Markers;
	XPoints m_XPoints;
	Cameras     * m_Cameras;
	MCamera     * m_SelectedCamera;

	/** Camera light coolness value */
	double        m_CameraLightCoolness;

	TrackerToolTransformContainerType     m_ToolTransformBuffer;

	/** Error map container */
	static ErrorCodeContainerType   m_ErrorCodeContainer;
	static ErrorCodeContainerType   m_MeasurementHazardCodeContainer;

	/** boolean to indicate if error code list is created */
	static bool m_ErrorCodeListCreated;

	/** Container holding status of the tools */
	std::map< std::string, int >  m_ToolStatusContainer;



	std::vector<std::string> m_ReferencePrefixes;

	itk::SmartPointer < misTrackingObserver> m_TrackerObserver; 
	bool m_CameraAttachedAlready;
	bool m_AutoCalculateLightCoolness;
	int	_MtTimerTickCurrentFrameNo;
	bool isShowingHalfSize;
	bool m_ProcessXpoint;

};