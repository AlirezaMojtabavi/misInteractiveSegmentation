#pragma  once
#include "ISimpleDataPackage.h"
#include "IPlanEntryModifier.h"
#include "INavigationViewersNView.h"


class misGUIEvent;

// Visualize result of change in a misSimpleDataPackage
class IPackageDataVisualizer
{
public:
	virtual ~IPackageDataVisualizer() = default;
	virtual void Render(void) = 0;
	virtual void Reset() = 0;
	virtual void ShowPackageContentsInViewer(std::shared_ptr<ISimpleDataPackage> package) = 0;
	virtual void SetPackageContent(std::shared_ptr<ISimpleDataPackage> package) = 0;
		virtual ApproachAndModelInformationStrct GetSelectedObjectInformation() const = 0;
	virtual void SetSelectedObjectInformation(ApproachAndModelInformationStrct val) = 0;
	virtual misUID GetSelectedObjectInformationUID() const = 0;
	virtual misUID GetSelectedObjectParentUID() const = 0;
	virtual misUID GetSelectedObjectContainerUID() const = 0;
	virtual std::shared_ptr<ISimpleDataPackage> GetCurrentPackage() const = 0;
	virtual void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> val) = 0;
	virtual void CheckFlyZone() = 0;
	virtual void SetVirtualTipPosition(const double* val) = 0;
	virtual void ChangeColorOf3DModel(misColorStruct newColor) = 0;
	virtual std::weak_ptr<misPlanData> FindSelectedPlan(std::shared_ptr<PlanDataListDependencyTypedef> plans) = 0;
	virtual misImageAnd3DModelPropertiesSettingStrct Update3DModelSettingPanelPropertiesGUI() = 0;
	virtual misUID GetSelectedObjectPackegeUID () const = 0;
	virtual void SetSelectedObjectContainerUID(const misUID& parentImageUid) = 0;
	virtual void SetSelectedObjectUID(const misUID& uid) = 0;
	virtual void SetSelectedPackageUID(const misUID& packageUId) = 0;
	virtual std::shared_ptr<ISimpleDataPackage> FindRelativePackageToCurrentPlan( misUID planUID ) = 0;
	virtual void setRealTimeSliders(bool isRealTime) = 0;
	virtual bool AnItemOnTreeViewIsSelected(ImageInformationStrct clickedItem, bool render = true) = 0;
	virtual bool ChangeImageWindow(misGUIEvent* pEvent) = 0;
	virtual bool ChangeImageLevel(misGUIEvent* pEvent) = 0;
	virtual bool ChangeImageColor(misGUIEvent* pEvent) = 0;
	virtual bool ChangeImageOpacity(misGUIEvent* pEvent) = 0;
	virtual bool Change3dModelColor(misGUIEvent* pEvent) = 0;
	virtual bool Change3DModelOpacity(misGUIEvent* pEvent) = 0;
	virtual bool ImageSettingTreeViewClicked(misGUIEvent* pEvent) = 0;
	virtual bool SetMarginValue(misGUIEvent* pEvent) = 0;
	virtual bool SetMarginAlarm(misGUIEvent* pEvent) = 0;
	virtual void UpdatePanoramicCurve() = 0;
	virtual void SetGroupViewer(std::weak_ptr<INavigationViewersNView> val) = 0;
	virtual bool UpdateSelectionInformation(ImageInformationStrct &clickedItem) = 0;
};