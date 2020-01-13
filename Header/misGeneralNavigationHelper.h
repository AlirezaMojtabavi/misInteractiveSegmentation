#pragma once

#include "ICheckPointsDistanceMeasurement.h"
#include "IFixedPointsDistanceMeasurment.h"
#include "IGeneralNavigationHelper.h"
#include "INavigationPackageFinder.h"
#include "INavigationTrackingHelper.h"
#include "INavigationViewersNView.h"
#include "ITargetDistanceMeasurement.h"
#include "ITrackerFilterSelector.h"
#include "ITrackerImageSynchronizer.h"
#include "ITrackingTool.h"
#include "misAutoCaptureScreen.h"
#include "misAutoCaptureScreenStrcts.h"
#include "misEnums.h"
#include "misImageContainedPolyDataStructs.h"
#include "misSubSeqTreeViewEventProcessor.h"
#include "misTimeForActWithExteralForce.h"
#include "misToolFixationAnalysis.h"
#include "misVoreenRepresentation.h"
#include "INavigationLayoutFactory.h"
#include "IVolumeCropping.h"

// Manage general application business related to navigation surgery tool during surgery
class misGeneralNavigationHelper : public IGeneralNavigationHelper
{
public:	
	misGeneralNavigationHelper(std::weak_ptr<INavigationViewersNView> viewerCollection,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer, 
		std::shared_ptr<INavigationPackageFinder> packgeFinder,
		std::shared_ptr<IFixedPointsDistanceMeasurment> fixedPointDistanceMeasure,
		std::shared_ptr<ICheckPointsDistanceMeasurement> checpointMeasuremnet,
		std::shared_ptr<ITargetDistanceMeasurement> targetDistance,
		std::shared_ptr<ITrackerImageSynchronizer> toolSync, 
		std::shared_ptr<parcast::ITrackerFilterSelector> filterSelector,
		std::shared_ptr<INavigationLayoutFactory> layotFactory, 
		std::shared_ptr<IVolumeCropping> volumeCropping);

	bool ProcessRequest(misGUIEvent* pEvent) override;
	void UpdateStatus(long long int puls, bool freezed) override;
	void Render(void) override;
	void RealseAllResources(void) override;
	void ResetSetting() override;
	void Activate3DMeasurement( bool activationState ) override;
	void AdvancedTargetDistanceMeasurementState() override;
	void AdvancedSourceDistanceMeasurementState() override;
	void ActivateCheckPoints( bool activation ) override;
	bool IsDistanceToCheckPointsIsActive() override;
	LandmarkStateListTypdef GetDistanceToCheckPointsState() override;
	void AdvancedcCheckPointsState(int buttonNumbere ) override;
	void ActivateTargetPoints(bool activationStat) override;
	void AdvancedTargetPointState() override;
	parcast::Vector<double>  GetVectorToTargetPoint()  const override;
	int GetNumberOfActiveLandmark() override;
	LandmarkStateListTypdef GetTargetState() override;
	bool IsTargetPointtActive() override;
	virtual std::vector<PropertiesOfPixelInImageType> CheckFlyZone();
	void SetTargetPointPosition(parcast::PointD3 realPosition) override;
	bool Is3DMeasurmentControlStateActive() override;
	void SetFreezState(bool freezState) override;
	void ChangeWidgetType(misCursorType cursorType) override;
	void UpdateAutomaticCaptureScreenWithToolsVisibility() override;
	void UpdateSettingFromAppSetting() override;
	void SetcCaptureScreenSetExternalActivation(misCaptureScreenStatus captureStatus) override;
	LandmarkStateListTypdef GetMeasurementLandamrkState() override;
	std::vector<std::string> GetValidDynamicLayoutsForSelectedPackage(misApplicationType appType, misUID selectedPackageUID) override;

	misCaptureScreenStatus GetCaptureScreenActionStatus() override;

	misUID FindDefaultPackage(std::string reference) override;
	
	// Reset all 2d viewers to initialized zoom state
	void Reset2DZoom() override;
	bool GetCaptureScreentExternalActivation() override;
	bool GetActiveFullScreenGetActivation() override;
	double GetSnapshotTakerActionValue() override;
	bool GetSnapshotTakerActivation() override;

	void DisableAutomaticCaptureScreen() override;
	misNearsetLandmarkStr UpdateDistanceInformationToCheckPoints(bool navigationToolIsVisible) override;
	bool GetIsObliqueView() const override;
	void SetIsObliqueView(bool val) override;
	double Get3DMeasurmentDistance() override;
	void Update3DMeasurmentInformation(bool freezState) override;
	virtual misUID GetReferenceUID() ;
	std::shared_ptr<IGroupViewerSetting> GetViewerLayout() override;

	void SetGroupViewer(std::weak_ptr<INavigationViewersNView> val) override;
private:
	typedef std::set<std::shared_ptr<ITrackingTool>> ToolListType;
	typedef itk::Vector<double, 3> VectorType;
	void Update3DDistanceLandmarks(std::vector<itk::Point<double, 3>> points);
	void AddMeasurmentLandmarks( std::vector<itk::Point<double, 3>> &points, LandmarkStateListTypdef buttonState );
	int UpdateCheckPointLandmarks(std::vector<itk::Point<double, 3>> points);
	void AddTargetPointLandmark( LandmarkStateListTypdef buttonState, double * position );
	void AddDistanceCheckingLandamrks( std::vector<itk::Point<double, 3>> &distanceCheckPoints );
	void UpdateTargetPointLandmarks();
	
	bool EnableLowPassFilter(bool enabled);
	bool IsCompositePackageNeeded(const std::string& layoutType);

	std::weak_ptr<IImage> m_pImageData;	// represents a 3D volume

	bool m_EraseState;
	bool m_ErasedObjCurrentDisplayStatus;
	bool m_WindowLevelTransFuncUpdateNeeded;
	bool m_ToolProjectionStatus;
	bool m_IsObliqueView;
	bool m_GeneralNoFlyZoneSound;
	bool m_GeneralNoFlyZoneFlag;
	bool m_VideoStatus;
  	misToolFixationAnalysis m_SnapshotTaker; 
	misAutoCaptureScreen m_AutomaticCaptureScreen;
	misTimeForActWithExteralForce m_AutomaticActiveFullScreen;	
	misTimeForActWithExteralForce m_AutomaticMaximizeVideoWindow;
		// Rendering tool properties
	bool m_IsMaxilarySurgeryType;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	misDatasetManager* m_DataSetManger;
	
	// An object in charge of managing all the viewers within the scene
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	misApplicationSetting* m_AppSetting;
	std::shared_ptr<ITargetDistanceMeasurement> m_DistanceToTarget;
	std::shared_ptr<ICheckPointsDistanceMeasurement> m_DistanceToCheckPoint;
	std::shared_ptr<IFixedPointsDistanceMeasurment> m_FixedPointsDistanceMeasure;
	std::shared_ptr<INavigationTrackingHelper> m_TrackingHelper;
	std::shared_ptr<INavigationPackageFinder> m_PackageFinder;
	misUID m_ReferenceUID;
	bool m_FreezeState = false;
	std::shared_ptr<parcast::ITrackerFilterSelector> m_FilterSelector;
	std::shared_ptr<INavigationLayoutFactory>  m_LaytoutFactory;
	std::shared_ptr<IVolumeCropping> m_VolumeCropper;

};