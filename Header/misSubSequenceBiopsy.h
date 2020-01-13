#pragma once

#include "misBiopsyPlanRepresentation.h"
#include "misCaptureSeedPlanningObserver.h"
#include "misCoreEvents.h"
#include "misDataSetManager.h"
#include "misEnums.h"
#include "misImageContainedPolydata.h"
#include "misPlanData.h"
#include "misPlanFlowInformation.h"
#include "misPlanProcedureEvent.h"
#include "misPlanSTRCT.h"
#include "misSubSequence.h"
#include "misSubSeqTreeViewEventProcessor.h"

class misSubSequenceBiopsy : public misSubSeqTreeViewEventProcessor
{
public:
	misSubSequenceBiopsy(void);
	~misSubSequenceBiopsy(void);
	virtual void SetLogger(LoggerType* logger);

	bool ProcessRequest(misGUIEvent* pEvent);
	void InitialeGuiProcessing();
	void OnSelected();
	void TaskOnLeave();
	void RequestInitializeGUI(misStrctSubTabModel  dataTab);
	void UpdateSettingFromAppSetting(void);
	void RequestclickTreeviewItem();
	void Render();
	
	igstkStandardClassBasicTraitsMacro( misSubSequenceBiopsy, misSubSequence )  
	itkNewMacro(Self);
	
protected:
	misUID						m_CurrentPlanUID;
	int                         m_CurrentID;
	int							m_planFlowStepSize;
	bool						m_isPreviewStart;
	misPlanFlowInformation*     m_PlaneFlowInformation;
	misCineDirection			m_PlanFlowDirection;
	misCroppingDirectionInVR	m_CroppingDir;
	PlanningPointType			m_CurrentPointType;
	std::shared_ptr<PlanDataListTypedef> m_planDependency;

	virtual void	CreateNewApproach();
	virtual void	ShowTreeInformation();
	void			SetPackageContent();
	void			ShowCurrentPackageContentsInViewer();
	void			ShowPackageListInGUI();
	void			ShowTreePackageInGUI(){};
	void			DeleteEntryPoint();
	void			DeleteTargetPoint();
	void			AddLandmarkToBiopsyPlan(misLandmarkInfoStruct lndStr);
	virtual void	UpdatePointSelectingState();
	virtual void	UpdatePlanLine(void);
	misEventListTypedef GetEventToGui();

private:
	void CompleteProcess( Object *caller,const itk::EventObject& pEvent);
	void UpdataCroppingDirection(misCroppingDirectionInVR cropDir);
	void UpdateViewBasedOnCroppingDirection();
	void UpdataCroppingDirectionInGUI();

	void StartPlanFlow();
	void StopPlanFlow();
	void SetPlanFlowSlider(double val,int planIndex);

	void RetrieveTemporaryDependendies();
	void ShowTransparentTemporaryVolume();
	void ResetSetting(void);
	void RealseAllResources(){}
	void UpdateStatus(long long int puls);

};
