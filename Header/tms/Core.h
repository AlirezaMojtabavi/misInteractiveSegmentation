#ifndef MISCORE_H_HEADER_INCLUDED_B807291F
#define MISCORE_H_HEADER_INCLUDED_B807291F

#using <mscorlib.dll>

#include "MIS3DInteractionStyle.h"
#include "igstkObject.h"
#include "igstkPulseGenerator.h"
#include "igstkStateMachine.h"
#include "igstkmacros.h"
#include "itkStdStreamLogOutput.h"
#include "itkimagebase.h"
#include "misCoreEvents.h"
#include "CoreProxy.h"
#include "misDataProcedure.h"
#include "misDataSetManager.h"
#include "misDatasetIO.h"
#include "misEnums.h"
#include "misFileReader.h"
#include "misGUITypes.h"
#include "misGeneralEvents.h"
#include "misGroupTab.h"
#include "misImageViewer.h"
#include "misInteractorSTyleImageExtend.h"
#include "misMacros.h"
#include "misResult.h"
#include "misSeconderyNeededHeader.h"
#include "misSolutionControl.h"
#include "misStrctGUIModel.h"
#include "misStrctSubTabModel.h"
#include "misStrctTabModel.h"
#include "vcclr.h"
#include "vtkActorCollection.h"

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

#include <vcclr.h>
#include "misTrackingProdecure.h"
#include "misTrackingEvents.h"
using namespace igstk;
using namespace itk;

//this class  represent a  combination of  Sequences and  their relation's For OV Application
//any link between Sequences and Sequence with gui must placed in CoreCallback

namespace tms
{
	class Core :public CoreProxy
	{
	public:
		igstkStandardClassBasicTraitsMacro(Core, CoreProxy);
		igstkNewMacro(Self);
		~Core();

		virtual void AddSequneces();


		void Addregistration();
		void PrepareResourceInBackground();
		virtual void CoreCallback(itk::Object *caller, const itk::EventObject &event);
		virtual void  LoadResources();
	private:
		Core();
		void                  ApplyLice(LicenseInformation liInfo);

		virtual void AddEvents();
		void SendNewToolDetectionEvent(void);
		void SetLoggingProperties();
		void StartToolCalibration(const misNewDetectedToolEventCore &event);
		void ApplySubSegStates(const ApplySubSegStatesEventToGUICore& ev);
		void ResetRegistration();
		void AddTool(const misAddedToolEventCore& ev);
		void StartTrackerViewing();

		// Add navigation sequence to project
		void AddNavigationSequence();

		// Determines whether the tool accuracy dialog is currently busy so as not to display it again if a calibration request for
		// another tracker tool is received.
		bool m_IsToolAccuracyBusy;

		misTrackingProdecure::Pointer  m_TrackingProc;
		HANDLE hResourceCreationThread;
	};
}
//
//
//
#endif /* MISCORE_H_HEADER_INCLUDED_B807291F */
