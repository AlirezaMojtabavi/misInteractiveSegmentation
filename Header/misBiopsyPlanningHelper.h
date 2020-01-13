#pragma once
#include "IBiopsyPlanningHelper.h"
#include "IBiopsyPlanningUIUpdater.h"
#include "INavigationViewersNView.h"
#include "IDatasetManager.h"
#include "IPackageDataVisualizer.h"
#include "ISimpleDataPackage.h"
#include "misPlanFlowInformation.h"
#include "misVolumeCropping.h"
#include "IScrewPlanView.h"
#include "misBiopsyPlanningUIUpdater.h"
#include "IBiopsyPlanningSolidSkinViewer.h"
#include "BiopsyPlanningFlow.h"
#include "IBiopsyAcceptPlan.h"
#include "IPlanSelector.h"
#include "misVertebraScrewPlanData.h"

class misBiopsyPlanningHelper :public IBiopsyPlanningHelper
{
public:
	misBiopsyPlanningHelper(std::shared_ptr<IBiopsyPlanningUIUpdater> observer, std::shared_ptr<INavigationViewersNView> groupViewer,
		IDatasetManager* datasetManager, std::shared_ptr<IPackageDataVisualizer> packageVisualizer, std::shared_ptr<IBiopsyPlanningSolidSkinViewer>,
		PlanFlowParameter plannigFlowParam);


	bool AcceptPlan(const BiopsyPlanInformation &planInformation) override;
	bool ChangePlanColor(const misColorStruct &color) override;
	bool CreateNewApproach() override;
	bool DeleteEntryPoint() override;
	bool DeleteTargetPoint() override;
	bool DenyPlan() override;
	bool ModifyEntryPoint() override;
	bool ModifyTargetPoint() override;
	bool SetEntryPoint() override;
	void SetPlanFlowSlider(const double &value) override;
	bool SetPlanTrancparency(const ApproachAndModelOpacityInformation &opacity) override;
	bool SetTargetPoint() override;
	bool ShowSelectedPackage(const misUID& newPackageUID) override;
	void StartPlanFlow() override;
	void StopPlanFlow() override;
	bool UpdateCroppingDirectionInViewes(const misCroppingDirectionInVR &direction) override;
	bool UpdatePackageList() override;
	void Render() override;
	void UpdateUITree(std::shared_ptr<ISimpleDataPackage> firstPackage)override;
	bool UpdateCompletetreeViewList(const PackageViewingListTypedef& packages) override;
	void SequenceActivated() override;
	void SequenceDeactivated() override;
	void SetFlowDirection(const misCineDirection &direction) override;
	void AddLandmarkToBiopsyPlan(const misLandmarkInfoStruct &lndStr) override;
	void UpdateCurrentPackage(const std::shared_ptr<ISimpleDataPackage> currentPackage) override;
	void SetObliqueFlag(bool isObique) override;
	void SelectPlan(const ApproachAndModelInformationStrct& item) override;
	misColorStruct GetColorFromSetting(const std::shared_ptr<const ISettingsContainer>& settings,
		const std::string& settingName) override;
	misColorStruct GetDefaultPlanColorFormSetting() override;
	void UpdatePlanColorInGUI() override;
	unsigned int GetNumberOfPlanes() override;
	void SetObliqueButtonState(bool isActive) override;
	bool IsSelectedPlane() override;
	void UpdateScrewWidget(const misScrewWidgetData& screwWidgetVal) override;

private:
	void UpdateUiByExistingPlanState() const ;
	void CreateNewPlan();
	void ShowSolidSkin();
	void UpdateCroppingDirection(misCroppingDirectionInVR croppingDirection);
	void UpdatePackageListInGUI();
	bool DeletePlan(std::weak_ptr<IPlan> planUnderEdit);
	void CancelCurrentPlan();
	void ChangeImageSelectedStatusBasedOnPlans();
	std::shared_ptr<IPlan> UpdateCurrentSelectedPlan();
	void FindPackageAutomatic();
	bool DeletePlanPoint(misLandmarkType lndType);
	void ModifyPlanPoint(misLandmarkType lndType);
	void UpdatePlanLine();
	void UpdatePointSelectingState();
	void ShowPlans(const ApproachAndModelInformationStrct& approachAndModelInformationStrct);
	void UpdatePlanPropertyIndicatorInGUI(std::weak_ptr<IPlan> plan);
	void DoForSelectedVertebraScrewPlan(std::function<void(std::weak_ptr<misVertebraScrewPlanData>)> toDo, const misUID& uid);
	std::shared_ptr<IPlan> GetActivePLan() const;
	std::string GetNewPlanName(std::shared_ptr<ISimpleDataPackage> package);
	std::shared_ptr<IBiopsyPlanningUIUpdater> m_UIUpdater;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
	IDatasetManager* m_DatasetManager;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<ISimpleDataPackage> m_Package;
	misColorStruct m_PlanColor;
	std::weak_ptr<IPlan> m_PlanUnderEdit, m_CurrentlySelectedPlan;
	PlanningPointType m_CurrentPointType;
	int m_CurrentID;
	misCroppingDirectionInVR	m_CroppingDir = NoCut;
	misCineDirection m_PlanFlowDirection;
	std::shared_ptr<misPlanFlowInformation>     m_PlaneFlowInformation;
	
	VolumeDataDependencyListTypes m_LastVolumes;
	misLandmarkInfoStruct m_TargetLandmarkRelation, m_EntryLandmarkRelation;
	std::shared_ptr<IVolumeCropping> m_VolumeCropping;
	std::shared_ptr<IBiopsyPlanningSolidSkinViewer> m_SolidSkinViewer;
	std::shared_ptr<BiopsyPlanningFlow> m_BiopsyPlanningFlow;
	std::shared_ptr<IBiopsyAcceptPlan> m_BiopsyAcceptPlan;
	std::shared_ptr<IPlanSelector> m_PlanSelector;
	misScrewWidgetData m_misScrewWidgetData;
	bool m_IsObique = false;
	
};




