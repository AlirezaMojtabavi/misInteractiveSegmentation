#pragma once
#include "misEventProxy.h"
#include "misStrctGUIModel.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "misGuiProxy.h"

class ISequenceManager;
class misGUIEvent;
class misApplicationSetting;
class misSolutionProperty;
class IDataBaseManager;
class ICoordinateSystemRepository;

class ICoreProxy : public misEventProxy
{

public:

	virtual void Init(misStrctGUIModel  model) = 0;
	virtual void  PulsePublish() = 0;
	//override to make new  Application
	virtual void AddSequneces() = 0;
	virtual bool AddSequence(std::shared_ptr<ISequenceManager> pSequnce,
		itk::Command*  pObserver, bool ForceToAdd = false) = 0;
	virtual void Start(void) = 0;
	virtual void Quit() = 0;
	virtual bool ProcessRequest(misGUIEvent* pEvent) = 0;
	virtual void SetGuiClient(misGuiProxy<ICoreProxy>* val) = 0;
	virtual std::shared_ptr<IDataBaseManager> GetDataBaseAccessLayer() const = 0;
	virtual std::shared_ptr<ICoordinateSystemRepository> GetCoordinateSystemRepository() const = 0;
	virtual misApplicationSetting*	GetAppSetting() const = 0;
	virtual std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCSCorrelationManager() const = 0;
	virtual std::shared_ptr<misSolutionProperty> GetSolutionProperty() const = 0;
	virtual void SetSolutionProperty(std::shared_ptr<misSolutionProperty> val) = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual void ImportPatient(std::string sourcePath) = 0;
 
};
