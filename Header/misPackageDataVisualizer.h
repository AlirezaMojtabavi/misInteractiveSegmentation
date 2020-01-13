#pragma once

#include "IPackageDataVisualizer.h"
#include "ISimpleDataPackage.h"
#include "misAnalysisStudioEvents.h"
#include "voreen\misCroppingDirectionInVR.h"
#include "misDataSetManager.h"
#include "misMultiViewSubSequence.h"

// The misPackageDataProcessor takes a data package as input and updates rendering section of groupviewer; Visualization is main 
// responsibility of misPackageDataProcessor 
class misPackageDataVisualizer : public IPackageDataVisualizer
{
public:

	misPackageDataVisualizer(std::weak_ptr<INavigationViewersNView> groupViewer);
	void Render(void) override;
	void Reset() override;
	void ShowPackageContentsInViewer(std::shared_ptr<ISimpleDataPackage> package) override;
	void SetPackageContent(std::shared_ptr<ISimpleDataPackage> package) override;
	ApproachAndModelInformationStrct GetSelectedObjectInformation() const override;
	void SetSelectedObjectInformation(ApproachAndModelInformationStrct val) override;
	misUID  GetSelectedObjectInformationUID() const override;
	misUID GetSelectedObjectParentUID() const override;
	misUID GetSelectedObjectContainerUID() const override;
	std::shared_ptr<ISimpleDataPackage> GetCurrentPackage() const override;
	void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> val) override;
	void CheckFlyZone() override;
	void SetVirtualTipPosition(const double* val) override;
	void ChangeColorOf3DModel(misColorStruct newColor) override;
	misImageAnd3DModelPropertiesSettingStrct Update3DModelSettingPanelPropertiesGUI() override;
	std::shared_ptr<ISimpleDataPackage> FindRelativePackageToCurrentPlan( misUID planUID ) override;
	std::weak_ptr<misPlanData> FindSelectedPlan(std::shared_ptr<PlanDataListDependencyTypedef> plans) override;
	misUID GetSelectedObjectPackegeUID() const override;
	void SetSelectedObjectContainerUID( const misUID& parentImageUid ) override;
	void SetSelectedObjectUID(const misUID& uid) override;
	void SetSelectedPackageUID(const misUID& packageUId) override;
	void setRealTimeSliders(bool isRealTime) override;
	bool AnItemOnTreeViewIsSelected(ImageInformationStrct clickedItem, bool render = true) override;
	bool UpdateSelectionInformation(ImageInformationStrct &clickedItem) override;
	bool ChangeImageWindow(misGUIEvent* pEvent) override;
	bool ChangeImageLevel(misGUIEvent* pEvent) override;
	bool ChangeImageColor(misGUIEvent* pEvent) override;
	bool ChangeImageOpacity(misGUIEvent* pEvent) override;
	bool Change3dModelColor(misGUIEvent* pEvent) override;
	bool Change3DModelOpacity(misGUIEvent* pEvent) override;
	bool ImageSettingTreeViewClicked(misGUIEvent* pEvent) override;
	bool SetMarginValue(misGUIEvent* pEvent) override;
	bool SetMarginAlarm(misGUIEvent* pEvent) override;
	void UpdatePanoramicCurve() override;
	void SetGroupViewer(std::weak_ptr<INavigationViewersNView> val) override;

private:

	void UpdateCurrentPackage();
	void ChangeContrastOfImage(misWindowLevelStr winLevelStr);
	void ChangeColorOfImage(misColorStruct newColor);
	void ChangeOpacityOfImage(float newOpacity);
	void ChangeOpacityOf3DModel(float newOpacity);
	void UpdateMargin( double MarginValue );
	double m_VirtualTipPosition[3];
	//Saves info about selected package and how we are going to show it.
	ApproachAndModelInformationStrct	 m_SelectedObjectInformation;
	misDatasetManager* m_DataSetManger;
	// a pointer to package you are working with
	std::weak_ptr<ISimpleDataPackage> m_CurrentPackage;
	// An object in charge of managing all the viewers within the scene
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	misApplicationSetting* m_AppSetting;
	std::weak_ptr<IImage> m_pImageData;
	bool m_IsRealTime;
};
