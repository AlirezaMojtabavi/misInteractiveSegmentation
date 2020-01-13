#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "misApplicationSetting.h"
#include "misCoordinateSystemRepository.h"
#include "misEnums.h"
#include "misEvent.h"
#include "misEventProxy.h"
#include "misEventSimulation.h"
#include "misGuiProxy.h"
#include "misObject.h"
#include "misSolutionControl.h"
#include "misStrctGUIModel.h"
#include "ReadNewSolutionEvent.h"

using namespace itk;

class misApplicationSetting;
class misGUIEvent;
class misGUIEventConvertor;
class misGUIInteractionDispatchers;
class misSequenceManager;
class misDatasetManager;

//this class  represent a  combination of  Sequences and  their relation's in general
namespace tms
{
	class CoreProxy :public  misOldObject, public misEventProxy
	{
	public:

		igstkStandardClassBasicTraitsMacro(CoreProxy, misOldObject);
		typedef itk::MemberCommand< Self >   ObserverType;
		CoreProxy();
		~CoreProxy();
		void	Init(misStrctGUIModel  model);
		bool ProcessRequest(misGUIEvent* pEvent) override;
		void  PulsePublish();
		//override to make new  Application
		virtual void AddSequneces() = 0;
		bool AddSequence(misSequenceManager* pSequnce, itk::Command*  pObserver, bool ForceToAdd = false);
		void Start(void);
		void Quit();
		void SetGuiClient(misGuiProxy<CoreProxy>* val);
		std::shared_ptr<misDataBaseManager> GetDataBaseAccessLayer() const;
		std::shared_ptr<ICoordinateSystemRepository> GetCoordinateSystemRepository() const;
		TabAbstractStateListTypdef  GetGUIAbstractState(void);
		// Start the application 
		misApplicationSetting*		GetAppSetting() const;
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCSCorrelationManager() const;
		std::shared_ptr<misSolutionProperty> GetSolutionProperty() const;
		void SetSolutionProperty(std::shared_ptr<misSolutionProperty> val);

	protected:

		void SaveSoloution(misSaveSolutionMode  savingMode, std::string subTabName);
		void InitGuiFromDescribtion(misStrctGUIModel  pModeDescribtion);
		//events that related  to All Sequences
		bool ConvertGeneralEvents(const EventObject & event);

		void RefreshGUI();

		virtual void CoreCallback(itk::Object *caller, const itk::EventObject &event);
		void CreatePulseGenrator();
		void InitLogger();
		virtual void AddEvents() = 0;
		void UpdateMainMenuInGUI(void);
		void AddWindowObserver(misStrctGUIModel  guiData, itk::Command* pObsever);
		void AddEventToAllSubSequence(misEvent &desiredEvent, itk::Command* observer);
		void AddGeneralEvents(itk::Command*  pObserver);
		void ShareContexts();
		//load any resource before when it needed
		virtual void  LoadResources() = 0;
		void						UpdateSubSequebceActivity(void);

		LicenseInformation m_LiInfo;
		bool							   m_Quit;
		bool							   m_EventProcessed;
		igstk::PulseGenerator::Pointer	   m_PulseGenerator;
		misSolutionControl::Pointer        m_SolutionControler;
		misGUIInteractionDispatchers*      m_GUIInteractionDispatchers;
		misStrctGUIModel		           m_guiModel;
		misGuiProxy<CoreProxy>*			   m_GuiClient;
		itk::MemberCommand<Self>::Pointer  m_CoreObserevr;
		std::vector<misGUIEventConvertor*> m_EventConvertors;
		std::shared_ptr<misDataBaseManager> m_DataBaseAccessLayer;
		std::shared_ptr<ICoordinateSystemRepository> m_CoordinateSystemRepository;

	private:
		bool ReadNewSoloution(const ReadNewSolutionEvent* pEvent);
		void LoadTFIMap();
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		std::shared_ptr<misSolutionProperty> m_SolutionProperty;
	};
}