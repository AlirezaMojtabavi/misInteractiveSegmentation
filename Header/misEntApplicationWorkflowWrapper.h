#pragma once

#include "misClrMarshallingUtil.h"
#include "misEntApplicationWorkflow.h"
#include "misDataUploadingWorkflowStepWrapper.h"

namespace misAppControlClrWrapper
{

	// The misSettingsContainerWrapper creates and encapsulates a misEntApplicationWorkflow object and adapts it to CLR so it can 
	// be exposed to .NET applications.
	public ref class misEntApplicationWorkflowWrapper
	{
	public:

		misEntApplicationWorkflowWrapper(std::shared_ptr<misEntApplicationWorkflow> workflowNative);
		!misEntApplicationWorkflowWrapper();
		~misEntApplicationWorkflowWrapper();

		property System::String^ CurrentWorkflowStep
		{
			System::String^ get()
			{
				return misClrMarshallingUtil::FromStdString((*m_WorkflowNative)->GetCurrentWorkflowStepId());
			}
			void set(System::String^ newStep)
			{
				(*m_WorkflowNative)->SetCurrentWorkflowStepId(misClrMarshallingUtil::ToStdString(newStep));
			}
		}

		property misDataUploadingWorkflowStepWrapper^ DataUploadingStep
		{
			misDataUploadingWorkflowStepWrapper^ get()
			{
				return gcnew misDataUploadingWorkflowStepWrapper((*m_WorkflowNative)->GetDataUploadingStep());
			}
		}

		void UpdateStatus();

		MIS_HAS_EVENTS_CLR_WRAPPER;
		MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC(CurrentStepChanged, System::String^ prevStepId, System::String^ currentStepId);
		MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC(StepAvailabilityChanged, System::String^ stepId, bool isAvailable);
		
	private:
		MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER(
			CurrentStepChanged, const std::string& previousStepId, const std::string& currentStepId)
		{
			CurrentStepChangedEvent(
				misClrMarshallingUtil::FromStdString(previousStepId), misClrMarshallingUtil::FromStdString(currentStepId));
		}

		MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER(StepAvailabilityChanged, const std::string& stepId, bool isAvailable)
		{
			StepAvailabilityChangedEvent(misClrMarshallingUtil::FromStdString(stepId), isAvailable);
		}

		std::shared_ptr<misEntApplicationWorkflow>* m_WorkflowNative;
	};

}
