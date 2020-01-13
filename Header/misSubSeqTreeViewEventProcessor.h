#pragma once

#include "misMultiViewSubSequence.h"
#include "ApproachAndModelInformationStrct.h"

class misWindowLevelStr;
class misDatasetManager;
struct misColorStruct;

class  misSubSeqTreeViewEventProcessor : public misMultiViewSubSequence
{
public:

	misSubSeqTreeViewEventProcessor(std::shared_ptr<INavigationViewersNView> groupViewer, std::shared_ptr<misSoftwareInformation> softwareInformation);

	bool ProcessRequest(misGUIEvent* pEvent);
	void Render();
	virtual void ShowTreeInformation() = 0;
	virtual void SetPackageContent() = 0;
	virtual void ShowCurrentPackageContentsInViewer() = 0;
	virtual void ShowTreePackageInGUI() = 0;
	virtual void ShowPackageListInGUI() = 0;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

protected:

	virtual void ChangeColorOf3DModel(misColorStruct newColor);
	virtual void CheckFlyZone();
	void SetVisibility(bool isVisible);
	void ShowPolyDatasIn2D(bool showPolydataIn2D);
	void SetVisibilityofDimention(misPresentationDimension presentationDim, bool m_Visibility);
	void UpdateImageSettingPanelPropertiesGUI();
	void Update3DModelSettingPanelPropertiesGUI();
	void ChangeContrastOfImage(misWindowLevelStr winLevelStr);
	void ChangeColorOfImage(misColorStruct newColor);
	void ChangeOpacityOfImage(float newOpacity);
	void ChangeOpacityOf3DModel(float newOpacity);

	misDatasetManager* m_DataSetManger;
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	vtkTimerLog* m_testTimer;
	int m_testCounter;
	double m_testAvTime;
	std::vector<vtkTextActor*> FlyZoneStatusText;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
};
