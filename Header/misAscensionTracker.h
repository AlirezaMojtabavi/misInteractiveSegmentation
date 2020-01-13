#pragma once

#include "igstkAscension3DGTracker.h"
#include "misCoreEvents.h"
#include "misTypes.h"
#include "misEnums.h"
#include "misTrackingManagerTypes.h"
#include "misStrctConnectOption.h"

#include "misSurfaceRepresentation.h"
#include "mis3DViewer.h"
#include "misTrackingManagerExports.h"

///////////////////////////////////////////////////////////////
//-M.A- I`m not sure of using these

class vtkproperty;
class vtkpointdata;
class vtkCellArray;
class vtkTransform;
class vtkConeSource;
class vtkFloatArray;
class vtkPlaneSource;
class vtkwin32OpenGLRenderWindow;

namespace igstk
{
	class Logger;
	class Transform;
	class AscensionTracker;
	class TransformObserver;
	class AscensionTrackerTool;
	class SerialCommunication;
	class SerialCommunicationSimulator;
}
class misTracking;
class misToolData;
class mis3DViewer;
class misSequenceManager;
class misTrackingObserver;
class misApplicationSetting;
class misigstkToolCalibration;
class misSurfaceRepresentation;
class misTrackingNeededObservers;
class misToolManager;
class misSequenceManager;
class misApplicationSetting;

// To each hardware port on the EM tracker device (0, 1, 2, 3, 4) a serial number is assigned which must match the serial number
// defined in tracker tool XML file.
class TRACKINGEXPORT misAscensionTracker :	public igstk::Ascension3DGTracker
{
public:
	typedef misAscensionTracker			Self;
	typedef itk::SmartPointer<Self>		Pointer;
	static  Pointer New(void); 
	bool Connect(double CurrentFrequency);
 	//stores serialNumber of tools attached to tracker and also the ports they are attached to
	std::map<ULONG, int> m_SerialNumberofToolsAttachedToTracker;
	//
	void DetectSensorsAttachedToTrackerAndTheirPort();
	//Returns a map which contains the serial number and also the port they are connected
	std::map<ULONG, int>& GetToolsInformation();
	int GetPortBySerialNumber(ULONG SN);
	std::shared_ptr<const ICoordinateSystem> GetCameraCoordinateSystem() const;
	bool Reset();

private:
	misAscensionTracker(const Self&);		//purposely not implemented not by -M.A-
	void operator=(const Self&);		//purposely not implemented not by -M.A-
	itk::SmartPointer < misTrackingObserver >       m_TrackerObserver; 
	misStructPivotData					m_pivotResult;
	std::shared_ptr<const ICoordinateSystem> m_CameraCoordSys;

protected:
	misAscensionTracker(void);
	virtual ~misAscensionTracker(void);
	void InitializeRequiredParameters(double CurrentFrequency);
	bool OpenCommunication();
	bool CloseCommunication();


};

