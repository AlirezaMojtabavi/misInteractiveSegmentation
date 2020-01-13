#pragma once

#include "IDatasetManager.h"
#include "INavigationViewersNView.h"
#include "IPackageDataVisualizer.h"
#include "IBiopsyPlanningHelper.h"
#include "misPackageDataVisualizer.h"
#include "misTreeViewUIUpdater.h"
#include "misVolumeCropping.h"
#include "BiopsyPlanFlowParam.h"


namespace parcast
{
	class VisibilityManagement;
}

using namespace parcast;

class misBiopsyPlanningSubSequence : public misMultiViewSubSequence
{
public:

	misBiopsyPlanningSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		 std::shared_ptr<misTreeViewUIUpdater> treeViewUiUpdater,
		std::shared_ptr<IPackageDataVisualizer> pkgDataVisualizer, std::shared_ptr<misSoftwareInformation> softwareInformation, PlanFlowParameter planningFlowParam);
	misBiopsyPlanningSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		IDatasetManager* datasetManager,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer, std::shared_ptr<IBiopsyPlanningHelper> planningHelper,
		const std::string& sequenceName, const std::string& subsequenceName, std::shared_ptr<misSoftwareInformation> softwareInformation);
	void OnSelected();
	void TaskOnLeave();
	void RequestclickTreeviewItem();
	void Render();
	void RealseAllResources();
	void ChangePlanColor(const misColorStruct& color);
	bool ProcessRequest(misGUIEvent* pEvent);
	bool Crop(misCroppingDirectionInVR cropDirctin);
	void DenyAllPlans();
	void CreateNewApproach();
	void AcceptCurrentPlan(BiopsyPlanInformation planeProp);
	void ShowImage(ImageInformationStrct imaheInformation);
	void SetTargetPointSelctionMode();
	void SetEntryPointSelectionMode();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::shared_ptr<INavigationViewersNView> GetPlaningViewer();
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:

	void InitializeObject();
	void ResetSetting();
	void UpdateStatus(long long int puls);
	void UpdateSettingFromAppSetting();
	void CompleteProcess(itk::Object *caller, const itk::EventObject& pEvent);

	misEventListTypedef GetEventToGui();
public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<IBiopsyPlanningHelper> m_PlanningHelper;
	bool m_isPreviewStart;
	misCroppingDirectionInVR m_CroppingDir;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<misTreeViewUIUpdater> m_TreeViewUIUpdater;
	misDatasetManager* m_DataSetManger;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<misVolumeCropping> m_VolumeCropping;
	PlanFlowParameter m_PlanningFlowParam;
};

