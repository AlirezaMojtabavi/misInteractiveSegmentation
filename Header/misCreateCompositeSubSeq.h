#pragma once
#ifndef misCreateCompositeSubSeq_H
#define misCreateCompositeSubSeq_H

#include "misGroupViewer.h"
#include "misSimpleDataPackage.h"
#include "misSubSequence.h"
#include "misSubSeqTreeViewEventProcessor.h"
#include "IPackageDataVisualizer.h"
#include "ITreeViewUIUpdater.h"
#include "misEventFromGui.h"

class misDatasetManager;
class misApplicationSetting;
namespace parcast
{
	class VisibilityManagement;
}
using namespace parcast;

class  misCreateCompositeSubSeq : public misMultiViewSubSequence/*misSubSequence*/
{
	enum misPackageSelectState
	{
		NewPackageCreated,
		ExistedPackage
	};
public:

	misCreateCompositeSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer, 
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger, std::shared_ptr<misSoftwareInformation> softwareInformation);

	bool ProcessRequest(misGUIEvent* pEvent);
	void CreateNewCompositePackage();

	void UpdateSettingFromAppSetting();
	void UpdateStatus(long long int puls);
	void OnSelected();
	void RealseAllResources();
	void TaskOnLeave();
	void Render(void);
	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:
	void SetPackageContent();
	void ShowTreePackageInGUI();
	void UpdateNewPackage();
	void ShowCurrentPackageContentsInViewer();
	void ShowPackageListInGUI();
	void ModifyCurrentPackage();
	void SaveTemporaryDependencies();
	void RetrieveTemporaryDependendies();
	void DeleteCurrentPackage();
	void DeleteCurrentItemFromCompositePackage();
	void AcceptCompositePackage();
	void DenyCompositePackage();
	void ChangePackage();
	void UpdateDataSetManager();
	bool AddItemToPackage();
	bool AddImageToPackage();
	bool Add3DModelToPackage();
	bool AddSegmentedObjectToPackage();
	bool AddVolumeRenderingObjectToPackage();
	bool AddPlanToPackage();
	bool DeleteImageFromPackage();
	bool Delete3DModelFromPackage();
	bool DeletePlanFromPackage();
	bool DeleteAllImagesFromPackage();
	bool DeleteAll3DModelsFromPackage();
	bool DeleteAllPlansFromPackage();
	bool CheckIfCorrelationTransformExisted(misUID firstImage, misUID secondImage);
	void SetItemVisibility2D(const ApproachAndModelVisibilityInformation& eventDat);
	void SetVisibilty2D(const ApproachAndModelVisibilityInformation& eventDat);
	void SetVisibilty3D(const ApproachAndModelVisibilityInformation&);

	misResultCode::ResultIds DeleteAllRelated3DModelsFromPackage(misUID parrentImageUID);

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	misPackageSelectState				 m_PackSelectState;
	misUID								 m_newPackageUID;
	ImageDependencyListTypes				  m_TemporaryImages;
	ImageContainedPolydataDependencyListTypes m_TemporaryImageContaineds;
	VolumeDataDependencyListTypes			  m_TemporaryVolumeDatas;
	PlanDataListTypedef	m_TemporaryPlanDatas;

	std::shared_ptr<IPackageDataVisualizer> m_PackageDataVisualizer;
	std::shared_ptr<ITreeViewUIUpdater> m_TreeViewUiUpdater;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;

};

#endif  
