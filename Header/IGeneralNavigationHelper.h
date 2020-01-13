#pragma once

#include "misAutoCaptureScreenStrcts.h"
#include "misEnums.h"
#include "misGuiEvent.h"
#include "misGuiStructures.h"
#include "misPackageDataVisualizer.h"
#include "misImageContainedPolyDataStructs.h"

class IGeneralNavigationHelper
{
public:
	typedef itk::Point<double, 3> PointType;

	virtual bool ProcessRequest(misGUIEvent* pEvent) = 0;
	virtual void UpdateStatus(long long int puls, bool freezed) = 0;
	virtual void Render(void) = 0;
	virtual void RealseAllResources(void) = 0;
	virtual void ResetSetting() = 0;
	virtual void Activate3DMeasurement(bool activationState) = 0;
	virtual void AdvancedTargetDistanceMeasurementState() = 0;
	virtual void AdvancedSourceDistanceMeasurementState() = 0;
	virtual void ActivateCheckPoints(bool activation) = 0;
	virtual bool IsDistanceToCheckPointsIsActive() = 0;
	virtual LandmarkStateListTypdef GetDistanceToCheckPointsState() = 0;
	virtual void AdvancedcCheckPointsState(int buttonNumbere) = 0;
	virtual void ActivateTargetPoints(bool activationStat) = 0;
	virtual void AdvancedTargetPointState() = 0;
	virtual parcast::Vector<double> GetVectorToTargetPoint() const = 0;
	virtual int GetNumberOfActiveLandmark() = 0;
	virtual LandmarkStateListTypdef GetTargetState() = 0;
	virtual bool IsTargetPointtActive() = 0;
	virtual void SetTargetPointPosition(parcast::PointD3 realPosition) = 0;
	virtual bool Is3DMeasurmentControlStateActive() = 0;
	virtual void SetFreezState(bool freezState) = 0;
	virtual void ChangeWidgetType(misCursorType cursorType) = 0;
	virtual void UpdateAutomaticCaptureScreenWithToolsVisibility() = 0;
	virtual void UpdateSettingFromAppSetting() = 0;
	virtual void SetcCaptureScreenSetExternalActivation(misCaptureScreenStatus captureStatus) = 0;
	virtual LandmarkStateListTypdef GetMeasurementLandamrkState() = 0;
	virtual std::vector<PropertiesOfPixelInImageType> CheckFlyZone() = 0;

	virtual misCaptureScreenStatus GetCaptureScreenActionStatus() = 0;
	virtual misUID FindDefaultPackage(std::string reference) = 0;

	// Reset all 2d viewers to initialized zoom state
	virtual void Reset2DZoom() = 0;

	virtual bool GetCaptureScreentExternalActivation() = 0;
	virtual bool GetActiveFullScreenGetActivation() = 0;
	virtual double GetSnapshotTakerActionValue() = 0;
	virtual bool GetSnapshotTakerActivation() = 0;
	virtual void DisableAutomaticCaptureScreen() = 0;
	virtual misNearsetLandmarkStr UpdateDistanceInformationToCheckPoints(bool navigationToolIsVisible) = 0;
	virtual bool GetIsObliqueView() const = 0;
	virtual void SetIsObliqueView(bool val) = 0;
	virtual double Get3DMeasurmentDistance() = 0;
	virtual void Update3DMeasurmentInformation(bool freezState) = 0;
	virtual misUID GetReferenceUID() = 0;
	virtual std::shared_ptr<IGroupViewerSetting> GetViewerLayout() = 0;
	virtual void SetGroupViewer(std::weak_ptr<INavigationViewersNView> val) = 0;
	virtual std::vector<std::string> GetValidDynamicLayoutsForSelectedPackage(misApplicationType appType, misUID selectedPackageUID) = 0;
};