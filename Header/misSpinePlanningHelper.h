#pragma 

#include "IDatasetManager.h"
#include "IPackageDataVisualizer.h"
#include "IPlanningHelper.h"
#include "misPlanData.h"
#include "IPlanningHelperUIUpdater.h"
#include "IScrewCreator.h"
#include "IPlanAccepter.h"
#include "IPlanCanceler.h"
#include "IPlanSelector.h"
#include "IVolumeMaker.h"
#include "misGroupViewer.h"
#include "IScrewPlanDisplayer.h"
#include "IVertebraScrewPlanDataIterator.h"
#include "ScrewPlanView.h"
#include "IScrewPlanDeleter.h"

class misSpinePlanningHelper : public IPlanningHelper
{
public:
	misSpinePlanningHelper(std::shared_ptr<IPlanningHelperUIUpdater> uiUpdater,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		IDatasetManager* datasetManager, std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<parcast::IPlanRepo>, std::shared_ptr<IScrewCreator> screwFactory, std::shared_ptr<IPlanAccepter>,
		std::shared_ptr<IPlanCanceler> planCanceller, std::shared_ptr<IPlanSelector> planSelector,
		std::shared_ptr<parcast::IVolumeMaker> volumeMaker,
		std::shared_ptr<IVertebraScrewPlanDataIterator> screwIterator,
	std::shared_ptr<IScrewDisplayer> screwDiplayer,
		std::shared_ptr<parcast::IScrewPlanView> screwView, 
		std::shared_ptr<IScrewPlanDeleter> screwPlanDeleter);

	bool SelectApproachAndModelItem(const ApproachAndModelInformationStrct& item) override;
	void SelectApproachAndModelItem(misUID planId) override;
	bool SelectApproachAndModelSettings(const ApproachAndModelInformationStrct& item) override;
	void Render() override;	// Make private to see what happens (it probably doesn't need to be public).
	void UpdateUITree(std::shared_ptr<ISimpleDataPackage> firstPackage);
	void SequenceActivated() override;
	void SequenceDeactivated() override;
	void AddPlanPoint(const misLandmarkInfoStruct& lndStr) override;

	void UpdateViewersWithUnderEditingPlan();

	bool UpdatePackageList(const PackageViewingListTypedef&) override;
	bool ShowSelectedPackage(const misUID& newPackageUID) override;
	bool UpdateItemSelections(const ImageInformationStrct& clickedItem) override;
	bool SetScrewSourceType(ScrewWidgetSourceType widgetSrcType) override;
	void CreateScrew() override;
	bool SetStartPointState() override;
	bool SetEndPointState() override;
	void SetObliqueObserver(std::weak_ptr<misGroupViewer::IObliqueChanged> observer) override;
	bool ModifyStartPoint() override;
	bool ModifyEndPoint() override;
	bool DeleteStartPoint() override;
	bool DeleteEndPoint() override;
	bool SetScrewInteractionStyleToFree() override;
	bool SetScrewInteractionStyleToFreeLength() override;
	bool UpdateScrewColor(const misColorStruct& newColour) override;
	void AcceptPlan(const ScrewPlanInformation& planInfo, std::shared_ptr<ISimpleDataPackage> package) override;
	bool DeleteCurrentPlan() override;
	bool UpdateScrewWidth(double screwWidth) override;
	void UpdateScrewWidget(const misScrewWidgetData& screwWidgetVal) override;
	bool IsInModifyingMode() const override;
	std::weak_ptr<parcast::IPlan> GetCurrentlySelectedPlan() const override;

private:
	enum PointCaptureMode
	{
		NoCapture,
		AddingStartPoint,
		AddingEndPoint,
		ModifyingStartPoint,
		ModifyingEndPoint
	};

	void ChangeImageSelectedStatusBasedOnPlans();
	void FindPackageAutomatic();
	void FindCurrentAvailablePlan();
	void SetCurrentlySelectedPlan(std::weak_ptr<parcast::IPlan> plan, std::shared_ptr<ISimpleDataPackage> package);
	void SelectPlan(std::shared_ptr<ISimpleDataPackage> package);
	
	void SetStartPoint(const misLandmarkInfoStruct& lndStr);
	void SetEndPoint(const misLandmarkInfoStruct& lndStr);
	bool SetPointState(bool addingStartPoint);
	bool DeletePlanPoint(misLandmarkType lndType);
	bool ModifyPlanPoint(misLandmarkType lndType);
	void CancelCurrentPlan();

public:
	bool UpdateCompletetreeViewList(const PackageViewingListTypedef&) override;
	void ClearCompletetreeViewList() override;
private:
	std::shared_ptr<IPlanningHelperUIUpdater> m_UIUpdater;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView ;

	std::shared_ptr<parcast::IPlanRepo> m_PlanRepo;
	std::shared_ptr<parcast::IVolumeMaker> m_VolumeMaker;
	IDatasetManager* m_DataSetManger;
	std::shared_ptr<ISimpleDataPackage> m_Package;
	std::weak_ptr<parcast::IPlan> m_PlanUnderEdit, m_CurrentlySelectedPlan;
	misLandmarkInfoStruct m_TargetLandmarkRelation, m_EntryLandmarkRelation;
	misColorStruct m_PlanColor;
	double m_ScrewDiameter;
	PointCaptureMode m_PointCaptureMode;
	std::map<misUID, misUID> m_LastSelectedPlanOfPackage;
	std::shared_ptr<IScrewCreator> m_ScrewFactory;
	std::shared_ptr<IPlanAccepter> m_PlanAccepter;
	std::shared_ptr<IPlanCanceler> m_PlanCanceller;
	std::shared_ptr<IPlanSelector> m_PlanSelector;
	std::shared_ptr<IVertebraScrewPlanDataIterator> m_ScrewIterator;
	std::shared_ptr<IScrewDisplayer> m_ScrewDiplayer;
	std::shared_ptr<IScrewPlanDeleter> m_ScrewPlanDeleter;

	bool m_ModifyingPlanMode = false;
};
