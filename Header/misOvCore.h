#pragma once


#using <mscorlib.dll>

#include "MIS3DInteractionStyle.h"
#include "igstkObject.h"
#include "igstkPulseGenerator.h"
#include "igstkStateMachine.h"
#include "igstkmacros.h"
#include "itkStdStreamLogOutput.h"
#include "itkimagebase.h"
#include "misCoreEvents.h"
#include "misCoreProxy.h"
 #include "misDataSetManager.h"
#include "misDatasetIO.h"
#include "misEnums.h"
#include "misFileReader.h"
#include "misGUITypes.h"
#include "misGeneralEvents.h"
#include "misGroupTab.h"
#include "misVolumeSlicer.h"
#include "misInteractorSTyleImageExtend.h"
#include "misMacros.h"
#include "misResult.h"
#include "misSeconderyNeededHeader.h"
#include "misSolutionControl.h"
#include "misStrctGUIModel.h"
#include "misSubsequenceLayout.h"
#include "misStrctTabModel.h"
#include "vcclr.h"
#include "vtkActorCollection.h"
#include "misTrackingProdecure.h"
#include "misTrackingEvents.h"
#include "misTrackerConfigure.h"
#include "BiopsyToolTransformCalculator.h"
#include "misDataSequence.h"
#include "VolumeMaker.h"

#define USELOGGER

using namespace itk;
using namespace System;
using namespace System::Windows;
using namespace System::Reflection;
using namespace System::Windows::Controls;
using namespace System::Windows::Markup;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Windows::Input;
using namespace System::Windows::Interop;
using namespace igstk;
using namespace itk;

//this class  represent a  combination of  Sequences and  their relation's For OV Application
//any link between Sequences and Sequence with gui must placed in CoreCallback
class misOvCore :public misCoreProxy
{
public:

	misOvCore(std::shared_ptr<ISolutionControl> solutionCtrl,
		std::shared_ptr<IGUIInteractionDispatchers> guiDispacher,
		std::shared_ptr<ICoordinateSystemRepository> coordinateSystemRepo,
		std::shared_ptr<IDataBaseManager> dataBaseManger, std::shared_ptr<misSoftwareInformation> SoftwareInformation);


	virtual void AddSequneces();
	virtual void CoreCallback(itk::Object *caller, const itk::EventObject &event);
	virtual void LoadResources();
	virtual void PulsePublish() override;
	void Addregistration();
	void PrepareResourceInBackground();
	bool ProcessRequest(misGUIEvent* pEvent) final;

private:	

	virtual void AddEvents();
	void ApplyLice(LicenseInformation liInfo);
	void ObserveTrackerEvents();
	void SendNewToolDetectionEvent(void);
	void SetLoggingProperties();
	void StartToolCalibration(const misNewDetectedToolEventCore &event);
	void ApplySubSegStates(const ApplySubSegStatesEventToGUICore& ev);
	void ResetRegistration();
	void AddTool(const misAddedToolEventCore& ev);
	void StartTrackerViewing();
	void AddNavigationSequence();
	void AddDataProcedure(std::shared_ptr<parcast::VolumeMaker> volumeMaker);
	void AddPlanning( std::shared_ptr<parcast::VolumeMaker> volumeMaker);

	// Determines whether the tool accuracy dialog is currently busy so as not to display it again if a calibration request for
	// another tracker tool is received.
	bool m_IsToolAccuracyBusy;
	std::shared_ptr<misTrackingProdecure> m_TrackingProc;
	std::shared_ptr<misTrackerConfigure> m_TrackerConfig;
	HANDLE hResourceCreationThread;
	ITrackingSubsequenceViews* m_TrackingSeq;
	std::shared_ptr<misDataSequence> m_DataProcedure;
	std::shared_ptr<parcast::BiopsyToolTransformCalculator> m_ToolTransformCalculator;
};

