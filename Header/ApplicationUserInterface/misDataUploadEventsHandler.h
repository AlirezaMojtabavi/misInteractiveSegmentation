#pragma once

#include "misDataSetUploadinSubSeq.h"
#include "misEvent.h"
#include "misEventSimulation.h"
#include "misGUIInteractionDispatchers.h"
#include "misGuiProxy.h"
#include "misObject.h"
#include "misSolutionControl.h"
#include "misStrctGUIModel.h"

using namespace itk;

// This class  represent a  combination of  Sequences and  their relation's in general
class misDataUploadEventsHandler : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misDataUploadEventsHandler, misOldObject);
	typedef itk::MemberCommand< Self > ObserverType;

	misDataUploadEventsHandler(misDataSetUploadinSubSeq::Pointer subSeq, std::vector<misWindow*> windows, 
		gcroot<misGuiWrapper^> dataUploading, misStrctSubTabModel *subTabModel, misGUIInteractionDispatchers * gid);
	~misDataUploadEventsHandler();


private:
	void Init();
	void RefreshGUI();
	void InitGuiFromDescribtion(misStrctGUIModel  pModeDescribtion);
	void AddEventToSubSequence(misEvent& desiredEvent, itk::Command* observer);
	
	// Events that related to all sequences
	bool ConvertGeneralEvents(const EventObject & event);
	
	void CoreCallback(itk::Object *caller, const itk::EventObject &event);
	void AddWindowObserver(misStrctGUIModel  guiData, itk::Command* pObsever);
	void AddGeneralEvents(itk::Command*  pObserver);
	void ShareContexts();
	
	template <typename DestinationEventType, typename SourceEventType>
	bool ApplyRequestToGui(const SourceEventType& srcEv);

	template <typename DestinationEventType, typename SourceEventType>
	bool ApplyUnloadedRequestToGui(const SourceEventType& srcEv);
	void InitLogger();


	bool m_EventProcessed;
	igstk::PulseGenerator::Pointer m_PulseGenerator;
	misStrctGUIModel m_guiModel;
	itk::MemberCommand<Self>::Pointer m_CoreObserevr;

	std::vector<misGUIEventConvertor*> m_EventConvertors;
	std::shared_ptr<misSolutionProperty> m_SolutionProperty;
	std::vector<misWindow*> m_Windows;
	misDataSetUploadinSubSeq::Pointer m_SubSequence;
	gcroot<misGuiWrapper^> m_DataUploadingGUI;
	misStrctSubTabModel* m_SubTabModel;
	misGUIInteractionDispatchers* m_GUIInteractionDispatchers;
};
