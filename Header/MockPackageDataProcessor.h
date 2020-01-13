#pragma once

#include "IPackageDataVisualizer.h" 
#include "misGuiStructures.h"

MOCK_BASE_CLASS(MockPackageDataProcessor, IPackageDataVisualizer)
{
	MOCK_NON_CONST_METHOD(Render, 0, void(void) );
	MOCK_NON_CONST_METHOD(Reset, 0, void (void));
	MOCK_NON_CONST_METHOD(ShowPackageContentsInViewer, 1, void(std::shared_ptr<ISimpleDataPackage>));
	MOCK_NON_CONST_METHOD (UpdataCroppingDirection, 0, void (void) );
	MOCK_NON_CONST_METHOD(SetPackageContent, 1,  void(std::shared_ptr<ISimpleDataPackage>));
	MOCK_CONST_METHOD(GetCroppingDirection, 0, misCroppingDirectionInVR ());
	MOCK_NON_CONST_METHOD(SetCroppingDirection, 1, void(misCroppingDirectionInVR) );
	MOCK_CONST_METHOD(GetSelectedObjectInformation, 0, ApproachAndModelInformationStrct());
	MOCK_NON_CONST_METHOD(SetSelectedObjectInformation, 1, void(ApproachAndModelInformationStrct ) );
	MOCK_CONST_METHOD(GetSelectedObjectInformationUID, 0, misUID  () );
	MOCK_CONST_METHOD(GetSelectedObjectParentUID, 0, misUID() );
	MOCK_CONST_METHOD(GetSelectedObjectContainerUID, 0, misUID () );
	MOCK_CONST_METHOD(GetCurrentPackage, 0, std::shared_ptr<ISimpleDataPackage> ());
	MOCK_NON_CONST_METHOD(SetCurrentPackage,1, void(std::shared_ptr<ISimpleDataPackage> ) );
	MOCK_NON_CONST_METHOD (CheckFlyZone, 0, void () );
	MOCK_NON_CONST_METHOD(SetVirtualTipPosition,1, void(const double* ) );
	MOCK_NON_CONST_METHOD(ChangeColorOf3DModel, 1, void (misColorStruct) );
	MOCK_NON_CONST_METHOD(FindSelectedPlan, 1, std::weak_ptr<misPlanData> (std::shared_ptr<PlanDataListDependencyTypedef>));
	MOCK_CONST_METHOD(GetCurrentPlannedScrew, 0, std::weak_ptr<misPlanData> () );
	MOCK_NON_CONST_METHOD(Update3DModelSettingPanelPropertiesGUI, 0, misImageAnd3DModelPropertiesSettingStrct(void));
	MOCK_CONST_METHOD(GetSelectedObjectPackegeUID, 0, misUID() );
	MOCK_NON_CONST_METHOD(SetSelectedObjectContainerUID, 1, void(const misUID& ));
	MOCK_NON_CONST_METHOD(SetSelectedObjectUID , 1, void (const misUID&));
	MOCK_NON_CONST_METHOD(SetSelectedPackageUID, 1, void (const misUID&));
	MOCK_NON_CONST_METHOD(SetCurrentPlannedScrew, 0, void ());
	MOCK_NON_CONST_METHOD(FindRelativePackageToCurrentPlan, 1, std::shared_ptr<ISimpleDataPackage>(misUID));
	MOCK_NON_CONST_METHOD(SetViewersToCurrentScrew, 1, void(misUID param1));
	MOCK_NON_CONST_METHOD(setRealTimeSliders, 1, void(bool ));
	MOCK_NON_CONST_METHOD(SetVisibility2D, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(SetVisibility, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(SetVisibility3D, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ChangeImageWindow, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ChangeImageLevel, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ChangeImageColor, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ChangeImageOpacity, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(Change3dModelColor, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(Change3DModelOpacity, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ImageSettingTreeViewClicked, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(ShowSegmentedObjectIn2D, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(SetMarginValue, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(SetMarginAlarm, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(AnItemOnTreeViewIsSelected, 2, bool(ImageInformationStrct, bool));
	MOCK_NON_CONST_METHOD(UpdatePanoramicCurve, 0, void ());
	MOCK_NON_CONST_METHOD(SetGroupViewer, 1 , void (std::weak_ptr<INavigationViewersNView> ) );
	MOCK_NON_CONST_METHOD(UpdateSelectionInformation, 1, bool (ImageInformationStrct & ));

};