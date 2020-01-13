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
#include "misStrctGUIModel.h"
#include "ICoreProxy.h"
#include "ISolutionControl.h"
#include "IGUIInteractionDispatchers.h"
#include "IShareContexts.h"

using namespace itk;

class misApplicationSetting;
class misGUIEvent;
class misGUIEventConvertor;
class misGUIInteractionDispatchers;
class misSequenceManager;
class misDatasetManager;
class ReadNewSolutionEvent;

//this class  represent a  combination of  Sequences and  their relation's in general
class misCoreProxy: public ICoreProxy
{
public:

 	typedef itk::MemberCommand< misCoreProxy >   ObserverType;
	misCoreProxy(std::shared_ptr<ISolutionControl> solutionCtrl, 
		std::shared_ptr<IGUIInteractionDispatchers> guiDispacher, 
		std::shared_ptr<ICoordinateSystemRepository> coordinateSystemRepo,
		std::shared_ptr<IDataBaseManager> dataBaseManger,
		std::shared_ptr<misSoftwareInformation> m_SoftwareInformation);
 	void	Init(misStrctGUIModel  model)  override;
	virtual bool ProcessRequest(misGUIEvent* pEvent) override;

	void ImportPatient(std::string sourcePath) override;


	virtual void  PulsePublish();

	bool AddSequence(std::shared_ptr<ISequenceManager> pSequnce , itk::Command*  pObserver,bool ForceToAdd = false)  override;
	void Start(void) override ;
	void Quit() override;
	void SetGuiClient( misGuiProxy<ICoreProxy>* val ) override;
	std::shared_ptr<IDataBaseManager> GetDataBaseAccessLayer() const;
	std::shared_ptr<ICoordinateSystemRepository> GetCoordinateSystemRepository() const override;
	// Start the application 
	misApplicationSetting*		GetAppSetting() const override;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCSCorrelationManager() const override;
	std::shared_ptr<misSolutionProperty> GetSolutionProperty() const override;
	void SetSolutionProperty(std::shared_ptr<misSolutionProperty> val) override;


	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) override;


	virtual void InvokeEvent(const itk::EventObject& event) override;


	virtual bool HasObserver(const itk::EventObject & event) const override;

protected:

	void SaveSoloution(misSaveSolutionMode  savingMode, std::string subTabName);
	void InitGuiFromDescribtion(misStrctGUIModel  pModeDescribtion);
	//events that related  to All Sequences
	bool ConvertGeneralEvents( const EventObject & event );

	void RefreshGUI();

	virtual void CoreCallback( itk::Object *caller, const itk::EventObject &event);
	void CreatePulseGenrator();
	void InitLogger();
	virtual void AddEvents()=0;
	void UpdateMainMenuInGUI(void);
	void AddWindowObserver(misStrctGUIModel  guiData,itk::Command* pObsever);
	void AddEventToAllSubSequence( misEvent &desiredEvent, itk::Command* observer );
	void AddGeneralEvents(itk::Command*  pObserver);
	void ShareContexts();
	//load any resource before when it needed
	virtual void  LoadResources()=0;
	void						UpdateSubSequebceActivity(void);
	void PostProcessingGUIInteraction(misGUIEvent* pEvent);

	LicenseInformation m_LiInfo;
	bool							   m_Quit;
	bool							   m_EventProcessed;
	igstk::PulseGenerator::Pointer	   m_PulseGenerator;
	std::shared_ptr<ISolutionControl> m_SolutionControler;
	std::shared_ptr<IGUIInteractionDispatchers> m_GUIInteractionDispatchers;
	misStrctGUIModel		           m_guiModel ;
	misGuiProxy<ICoreProxy>* m_GuiClient;
	itk::MemberCommand<misCoreProxy>::Pointer  m_CoreObserevr;
	std::vector<misGUIEventConvertor*> m_EventConvertors;
	std::shared_ptr<IDataBaseManager> m_DataBaseAccessLayer;
	std::shared_ptr<ICoordinateSystemRepository> m_CoordinateSystemRepository;
	misLogger* m_Logger;
	std::shared_ptr<misSoftwareInformation> m_SoftwareInformation = nullptr;

private:

	bool ReadNewSoloution( const ReadNewSolutionEvent* pEvent );
	void LoadTFIMap();
	itk::Object::Pointer m_DummySubject = itk::Object::New();
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<misSolutionProperty> m_SolutionProperty;
	std::unique_ptr<IShareContexts> m_ContextShare;

};
