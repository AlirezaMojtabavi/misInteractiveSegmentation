
#include "IGeneralNavigationHelper.h"

MOCK_BASE_CLASS(MockGeneralNavigationHelper, IGeneralNavigationHelper)
{
	MOCK_NON_CONST_METHOD(ProcessRequest, 1, bool(misGUIEvent* pEvent));
	MOCK_NON_CONST_METHOD(UpdateStatus, 2, void(long long int puls, bool freezed));
	MOCK_NON_CONST_METHOD(Render, 0, void());
	MOCK_NON_CONST_METHOD(RealseAllResources, 0, void());
	MOCK_NON_CONST_METHOD(ResetSetting, 0, void());
	MOCK_NON_CONST_METHOD(Activate3DMeasurement, 1, void(bool activationState));
	MOCK_NON_CONST_METHOD(AdvancedTargetDistanceMeasurementState, 0, void());
	MOCK_NON_CONST_METHOD(AdvancedSourceDistanceMeasurementState, 0, void());
	MOCK_NON_CONST_METHOD(ActivateCheckPoints, 1, void(bool activation));
	MOCK_NON_CONST_METHOD(IsDistanceToCheckPointsIsActive, 0, bool());
	MOCK_NON_CONST_METHOD(GetDistanceToCheckPointsState, 0, LandmarkStateListTypdef());
	MOCK_NON_CONST_METHOD(AdvancedcCheckPointsState, 1, void(int buttonNumbere));
	MOCK_NON_CONST_METHOD(ActivateTargetPoints, 1, void(bool activationStat));
	MOCK_NON_CONST_METHOD(AdvancedTargetPointState, 0, void());
	MOCK_CONST_METHOD(GetVectorToTargetPoint, 0, parcast::Vector<double>());
	MOCK_NON_CONST_METHOD(GetNumberOfActiveLandmark, 0, int());
	MOCK_NON_CONST_METHOD(GetTargetState, 0, LandmarkStateListTypdef());
	MOCK_NON_CONST_METHOD(IsTargetPointtActive, 0, bool());
	MOCK_NON_CONST_METHOD(SetTargetPointPosition, 1, void(parcast::PointD3));
	MOCK_NON_CONST_METHOD(Is3DMeasurmentControlStateActive, 0, bool());
	MOCK_NON_CONST_METHOD(SetFreezState, 1, void(bool freezState));
	MOCK_NON_CONST_METHOD(ChangeWidgetType, 1, void(misCursorType cursorType));
	MOCK_NON_CONST_METHOD(UpdateAutomaticCaptureScreenWithToolsVisibility, 0, void());
	MOCK_NON_CONST_METHOD(UpdateSettingFromAppSetting, 0, void());
	MOCK_NON_CONST_METHOD(SetcCaptureScreenSetExternalActivation, 1, void(misCaptureScreenStatus captureStatus));
	MOCK_NON_CONST_METHOD(GetMeasurementLandamrkState, 0, LandmarkStateListTypdef());
	MOCK_NON_CONST_METHOD(CheckFlyZone, 0, std::vector<PropertiesOfPixelInImageType>());
	MOCK_NON_CONST_METHOD(SetObliqueFlag, 1, void(bool isOblique));
	MOCK_NON_CONST_METHOD(GetCaptureScreenActionStatus, 0, misCaptureScreenStatus());
	MOCK_NON_CONST_METHOD(FindDefaultPackage, 1, misUID(std::string reference));
	MOCK_NON_CONST_METHOD(Reset2DZoom, 0, void());
	MOCK_NON_CONST_METHOD(GetCaptureScreentExternalActivation, 0, bool());
	MOCK_NON_CONST_METHOD(GetActiveFullScreenGetActivation, 0, bool());
	MOCK_NON_CONST_METHOD(GetSnapshotTakerActionValue, 0, double());
	MOCK_NON_CONST_METHOD(GetSnapshotTakerActivation, 0, bool());
	MOCK_NON_CONST_METHOD(DisableAutomaticCaptureScreen, 0, void());
	MOCK_NON_CONST_METHOD(UpdateDistanceInformationToCheckPoints, 1, misNearsetLandmarkStr(bool navigationToolIsVisible));
	MOCK_CONST_METHOD(GetIsObliqueView, 0, bool());
	MOCK_NON_CONST_METHOD(SetIsObliqueView, 1, void(bool val));
	MOCK_NON_CONST_METHOD(Get3DMeasurmentDistance, 0, double());
	MOCK_NON_CONST_METHOD(Update3DMeasurmentInformation, 1, void(bool freezState));
	MOCK_NON_CONST_METHOD(GetReferenceUID, 0, misUID());
	MOCK_NON_CONST_METHOD(GetViewerLayout, 0, std::shared_ptr<IGroupViewerSetting>());
	MOCK_NON_CONST_METHOD(SetGroupViewer, 1, void(std::weak_ptr<INavigationViewersNView> val));
	MOCK_NON_CONST_METHOD(GetValidDynamicLayoutsForSelectedPackage, 2, std::vector<std::string>(misApplicationType 
		, misUID ) );
};