#pragma once

#include "misSubsequenceGUIWrapper.h"
#include "misFlyZoneDisplayer.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;

ref class misCaptureCommands;
ref class misTrackingDeviceMessenger;
ref class misRendererLibraryWrapperGUI;
ref class misShowPackageListGUI;
ref class misTreeViewPreparationFromPackageListGUI;
ref class misToolMarkerStatusReport;
ref class misLayoutSelectorGUI;
enum misCaptureScreenStatus;
struct PropertiesOfPixelInImageStr;
typedef std::vector<PropertiesOfPixelInImageStr> PropertiesOfPixelInImageType;

namespace WrapperGuiProxy
{
	ref class misTrackingViewerGUI;
}

namespace SpineNavigation
{
	enum  misVirualTipLengthValueOrder
	{
		Next,
		Previous
	};
}

ref class misSpineNavigationGUI : public misSubsequenceGUIWrapper
{
public:
	misSpineNavigationGUI(GUILibrary::misSpineNavigation^ window, misToolMarkerStatusReport^ toolMarkerInformation);
	~misSpineNavigationGUI();
	!misSpineNavigationGUI();
	virtual void MappingEvents()override;
	virtual void SetExtenalEventMethod(WrapperGUIBase::ExternalEventDelegate^ method) override;
	virtual void ApplyRequestToGUI(misGUIEvent*  pEvent) override;
	virtual void ResetGUIState() override;
	virtual void UpdateSettingFromAppSetting() override;
	virtual misRendererLibraryWrapperGUI^ GetRenderPackage()override;

	void UpdateSelectedPackageList();
	void FillTreeView_PackageList(PackageViewingListTypedef* list, bool autoNumber, String^ prefixText);
	void SetFreezState(bool isFreezed);
	void SetCaptureStatus(misCaptureScreenStatus newCaptureStatus);
	void HideToolMarkerStatus();
	void HideMessageBars();
	void SetMessageBarVisiblityFlag(bool flag);

	PackageViewingListTypedef* GetSelectedPackage(misUID packageUID);
	GUILibrary::misSpineNavigation^ m_mainWindow;

	misShowPackageListGUI^ showPackageListWindow;

protected:
	virtual void SetGUIState(ApplySubSegStatesEventToGUI* pEvent) override;
	virtual System::Windows::Window^ misSpineNavigationGUI::get_mainWindow() override;
	virtual System::Windows::Controls::UserControl^  getUserControl() override;
	virtual void LeavingSubsequence() override;

private:

	void TreeView_PackageListItem_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void Image_Visibility_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void UserControl_Loaded(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void misButton_VirtualTorus_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_AutoMeasurement_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_ToolProjection_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Freez_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_Left_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_Right_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_Up_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_None_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_Bottom_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_Front_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_FrontUp_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Cut3DModel_FrontDown_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_SetPoint1_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_SetPoint2_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CheckPointIndicator_C1_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CheckPointIndicator_C2_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CheckPointIndicator_C3_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CheckPointIndicator_C4_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_TrackingViewer_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_RequestMainToolCalibration_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_ShowPackageList_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_ClosePackageListWindow_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_TargetPointIndicator_SetTarget_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void CheckBox_autoSnapShot_Checked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_autoSnapShot_UnChecked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_ReceiveNoFlyZoneMessages_Checked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_ReceiveNoFlyZoneMessages_Unchecked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_AutomaticVirtualTipExtension_Checked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_AutomaticVirtualTipExtension_Unchecked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_SoundForNoFlyZoneMessages_Checked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_SoundForNoFlyZoneMessages_Unchecked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void ComboBoxWidgetType_ItemClick(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void ComboBoxAutoSnapshot_ItemClick(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CheckPointIndicator_ExpandCollapse_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_DistanceIndicator_ExpandCollapse_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_CutDirectionIndicator_ExpandCollapse_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_TargetPointIndicator_ExpandCollapse_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_VirtualToolTipIndicator_ExpandCollapse_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void CheckBox_ActivateErasedPath_Click(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_ColorizeErasedPath_Click(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void VirtualToolTipIndicator_misButton_IncreaseToolTip_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void VirtualToolTipIndicator_misButton_DecreaseToolTip_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void VirtualToolTipIndicator_misButton_VirtualTip_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void VirtualToolTipIndicator_TextBox_ToolTipLength_TextChanged(System::Object^ sender, System::Windows::Controls::TextChangedEventArgs^ arg);
	void CheckBox_autoRecord_Checked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void CheckBox_autoRecord_Unchecked(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void misButton_RecordNavigationScene_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_RecordNavigationScene_TouchDown(System::Object^ sender, System::Windows::Input::TouchEventArgs^ arg);
	void misButton_layout_Clicked(System::Object ^sender, System::Windows::Input::MouseButtonEventArgs ^e);

	void SetVirtualTipTextBoxCursorToEnd();
	void UndoVirtualTipTextBoxText();

	void HideAllVisibliIndicators();
	void EnableAllControls();
	void DisableAllControls();
	void AutoMeasurmentOn();
	void AutoMeasurmentOff();
	void AutoTakeSnapshotOn();
	void AutoTakeSnapshotOff();
	void DistanceIndicatortOn();
	void DistanceIndicatorOff();
	void CheckPointIndicatorOn();
	void CheckPointIndicatorOff();
	void CutDirectionOn();
	void CutDirectionOff();
	void VirtualToolTipOn();
	void VirtualToolTipOff();
	void TargetPointOn();
	void TargetPointOff();
	void UpdateTakeAutoSnapshotSetting();
	void SetDistanceValue(double distanceValue);
	void SetDistancePointStates(LandmarkStateListTypdef distanceStruct);
	void SetTargetPointStatus(LandmarkStateListTypdef targetStatus);
	void SetTargetPointInfo(double dist, double x, double y, double z);
	void SetNearestLandmarkStates(LandmarkStateListTypdef distanceStruct);
	void SetNearestLandmardInfo(misNearsetLandmarkStr landmarkInfo);
	void InitializeComboBoxWidgetType(System::Windows::Controls::ComboBox^ widgetCombobox);
	void SelectComboboxWidgetTypeItem(misCursorType type, System::Windows::Controls::ComboBox^ comboBox);
	void InitializeComboBoxAutoSnapshotValues(System::Windows::Controls::ComboBox^ autoSnapshotCombobox);
	void ChangeFreezState();
	void DisplayToolStatus(misTrackingStateReport report);
	void ShowToolMarkerStatus(misTrackingToolMarkerReport toolInfo);
	void SetAutoSnapShotDuration(double val);
	void SetAutoSnapShotProgressBarValue(double val);
	void SetAutoSnapshotComboBoxValue(String^ val);
	void InitializeAutoSnapShotControls();
	void UpdateVirtualTipStatus();
	void UpdateCroppingBottonState();
	void SetVirtualTipLengthValue(SpineNavigation::misVirualTipLengthValueOrder order);
	void UpdateNoFlyZoneStates(std::vector<PropertiesOfPixelInImageType> noFlyZoneState);
	void UpdateLocalButtonStatus();
	void ShowBoardMessage(GuiBoardMessage message);
	void SetToolbarVisibilityStatus();


	bool HandleVirtualKeyEvent(CommandEnum enumEv);
	bool PrepareCaptureDevice();

	double GetAutoSnapShotDuration(System::Windows::Controls::ComboBoxItem^ item);
	double GetAutoSnapShotProgressBarValue();

	misCaptureCommands^ m_CaptureCommand;
	misTrackingDeviceMessenger^ m_TrackingDeviceInformation;
	misRendererLibraryWrapperGUI^ rendererPackage;
	misTreeViewPreparationFromPackageListGUI^ m_treeViewComplete;
	misToolMarkerStatusReport^ m_toolMarkerInformation;
	WrapperGuiProxy::misTrackingViewerGUI^ m_TrackingViewer;
	misLayoutSelectorGUI^ m_LayoutSelector;
	String^ selectedNodeID;
	String^ m_ToolTipLengthStr;

	misCroppingDirectionInVR m_CroppingDirection;
	misCaptureScreenStatus m_PlayingCaptureState;
	misToolProperties::ApplicationFlag m_CurrentInvisible;
	PackageViewingListTypedef* m_PackageList;

	misUID* selectedPackageUID;
	misUID* selectedObjectUID;

	double m_ToolTipLength;
	double m_TimeForAutoDisappearToolMarkerWindow;
	double m_FinalOpacityForAutoDisappearToolMarkerWindow;

	bool m_isFreezed;
	bool m_isAutoMeasurOn;
	bool m_isAutoTakeSnapshotOn;
	bool m_DistanceIndicatorStatus;
	bool m_CheckPointIndicatorStatus;
	bool m_TargetPointIndicatorStatus;
	bool m_TorusEnabled;
	bool m_ManualCapturingActivated;
	bool m_isPreviewStart;
	bool m_activateErasedPath;
	bool m_colorizeErasedPath;
	bool m_ToolMarkerVisibilityWindowDisplayed;
	bool m_MeasurmentWidget;
	void Spine3DStlClockwiseRotateOnMouseLeftButtonUp(System::Object ^sender, System::Windows::Input::MouseButtonEventArgs ^e);
	void Spine3DStlCounterClockwiseRotateOnMouseLeftButtonUp(System::Object ^sender, System::Windows::Input::MouseButtonEventArgs ^e);
	misFlyZoneDisplayer^ m_NoflyZoneMessageBar;
	bool m_MessageBoardsVisiblity;
	void LayoutSelectionChanged();
};

