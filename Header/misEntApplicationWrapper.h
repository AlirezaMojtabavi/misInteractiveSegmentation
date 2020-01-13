#pragma once

#include "misEntApplication.h"
#include "misEntApplicationWorkflowWrapper.h"
#include "misAppBase_misSettingsContainerWrapper.h"

using namespace System;

namespace misAppControlClrWrapper
{

	// The misSettingsContainerWrapper creates and encapsulates a misEntApplication object and adapts it to CLR so it can 
	// be exposed to .NET applications.
	public ref class misEntApplicationWrapper
	{
	public:
		misEntApplicationWrapper(Array^ argv);
		!misEntApplicationWrapper();
		~misEntApplicationWrapper();

		enum class Status
		{
			NotConstructed,
			NotInitialized,
			Initializing,
			Running,
			Exit
		};

		MIS_HAS_EVENTS_CLR_WRAPPER;

		property misSettingsContainerWrapper^ ApplicationSettings { misSettingsContainerWrapper^ get(); }
		property misEntApplicationWorkflowWrapper^ ApplicationWorkflow { misEntApplicationWorkflowWrapper^ get(); }
		property System::String^ VersionString { System::String^ get(); }
		property Status CurrentStatus { Status get(); }
		void UpdateStatus();

		MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC(CurrentStatusChanged, Status lastStatus, Status currentStatus);

	private:
		MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER(
			CurrentStatusChanged, misEntApplication::Status lastStatus, misEntApplication::Status currentStatus)
		{
			CurrentStatusChangedEvent(ConvertStatus(lastStatus), ConvertStatus(currentStatus));
		}

		Status ConvertStatus(misEntApplication::Status nativeStatus);

		misEntApplication* m_EntApp;
		int m_ArgC;
		char** m_ArgV;
	};

}