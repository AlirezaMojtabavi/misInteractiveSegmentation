#pragma once

#include "..\misRegistrationProdecure\misReportRegistrationResults.h"
#include "IUserMessageBoardManager.h"
#include "misDataSetManager.h"
#include "misExtractExternalSurface.h"
#include "misGuiEvent.h"
#include "misImageToPatientLandmarkBasedRegistation.h"
#include "misIterativeClosestPointTransform.h"
#include "misMultiViewSubSequence.h"
#include "misRegisterManagerTypes.h"
#include "misToolCoordinateSystemRenderer.h"
#include "misToolData.h"
#include "misToolFixationAnalysis.h"
#include "misTrackingStateReport.h"
#include "misTrackingStateReporter.h"
#include "misTrackingToolMarkerReporter.h"
#include "misTrackingToolQuery.h"
#include "SurfaceRegistrationDataStrct.h"
#include "ISurfaceRegistrationUIAdapter.h"
#include "IViewingTypeColormapSelector.h"

class misSeedRepresentation;
class misDatasetManager;
class misGroupViewer;
class misIterativeClosestPointTransform;
class misToolData;
class misToolFixationAnalysis;
class misToolLocator;

class misSurfaceRegistrationSubSequence : public misMultiViewSubSequence
{
public:
	misSurfaceRegistrationSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
	                                  std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
	                                  correlationManger,
	                                  std::shared_ptr<IViewingTypeColormapSelector> viewingTypeColormapSelector, 
		std::shared_ptr<misSoftwareInformation> softwareInformation);

	void SetViewr(std::shared_ptr<INavigationViewersNView> val);
	void SetTrackingState(CurrentSubSequenseStateStrct trackingState);
	void SetLandmarkList(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> val);
	void ResetSetting() override;
	void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage>);
	void ResetSurfaceRegistrationSubSeq();
	CurrentSubSequenseStateStrct GetTrackingState() const { return m_TrackingState; }
	std::shared_ptr<ISimpleDataPackage> GetTemporaryPackage() const { return m_TemporaryPackage; }
	void SetTemporaryPackage(std::shared_ptr<ISimpleDataPackage> val) { m_TemporaryPackage = val; }
	void SetPackage(std::shared_ptr<ISimpleDataPackage> hybridPack);
	void SetImage(std::shared_ptr<IImage> image);
	void AddRenderingTool(std::shared_ptr<ICoordinateSystemRenderer> renderingTool);
	void SetSurfaceRegisrationPolydata(vtkPolyData* surfaceRegistartionPolyData, double thresholdValue);
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:

	void ResetSurfaceRegistration() const;
	virtual void RealseAllResources();
	void UpdateSettingFromAppSetting() override;
	bool ProcessRequest(misGUIEvent* pEvent) override;
	void TaskOnLeave();
	void UpdateVolumeViewingType();
	void OnSelected();
	void UpdateStatus(long long int puls);
	void Render() override;

	void CheckAutomaticCaptureLandmark();
	void GeneratePolyFromTrackedPosition(vtkPoints* pSourcePOints, vtkPolyData* pSourcePointSet);
	vtkPolyData* GeneratePolyFromTrackedPosition(vtkPoints* previousCapturedPoints = 0) const;
	void ClaculateBoundingsOfTrackedPoints(int trackerPointSize, double * bounds);
	void UpdateLandmarkBasedRegistrationResult() const;
	void DeleteLastCapturedPoint();
	void CaptureLastToolPosition();

	// Important Note: This function must call at the first of updateStatus
	void UpdateToolStatus();
	bool CheckLastToolPositionValidity();
	tgt::dvec3 GetNavigationToolLatestPosition();
	void ComputeSurfaceRegistrion();
	void ShowResultFromSurfaceRegistrationInScene(vtkPoints* pSourcePOints);
	void RemoveResultFromSurfaceRegistrationInScene();
	void AddGeneratedTargetPolydataToViewer(vtkPolyData* pClippedPolyData);
	void AddSourcePolyDataToViewer(vtkPolyData* pSourcePolyData);
	void ResetOnContinue();
	void UpdateMaxPermitedErrorForLandmarkCapturing();
	void CkeckLastToolPositionDistanceToSurface();
	bool UpdateIsoSurfaceForSurfaceRegistration();
	void UpdateSurfaceRegistarionCalculator(vtkPolyData*  pPolyInput);
	double ComputeMinimumOfLastToolPositionDistanceToPreviouslandmarks(double* lastPosition);
	void UpdateCapturingProgressBarInGUI(double val);
	// Note : must call after UpdateCapturingProgressBarInGUI
	void UpdateSoundAlertStatus();
	void ShowTools(bool value);
	void UpdateView() const;
	void ClearSurfaceLandmarks();
	void AddNewSurfaceLandmark(double position[3]);
	void ResetToolStatus();
	misEventListTypedef GetEventToGui() override;
	vtkSmartPointer<vtkPolyData> GeneratePolyDataFromImage();


	// Examines visibility of tools with the specified application flag, and if such a tool is found that has been recently 
	// visible but is now invisible, creates the appropriate tool marker visibility status report event to be sent to GUI.
	// It returns true if the event was sent and false if sending of event for the specified application flag has not been needed.
	bool SendAppropriateToolMarkerVisibilityEvent(misToolProperties::ApplicationFlag appFlag);

	// Logger routine for saving registration results
	void LogRegisatrationResults();

	// Gets the tools state reporter object owned by this object. It is used for lazy construction of misTrackingStateReporter as
	// it needs other objects during construction which might not be available at construction time of this object. Always check
	// return value before use; returns NULL if construction is still not possible.
	std::shared_ptr<misTrackingStateReporter> GetToolStateReporter();
	std::shared_ptr<misTrackingToolMarkerReporter> GetToolMarkerReporter(std::shared_ptr<const ITrackingTool> tool);

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::vector<std::shared_ptr<misToolData>> m_TrackerList;
	itk::Command* m_pObserver{};
	std::vector<std::shared_ptr<misSeedRepresentation>> m_SeedList;
	std::shared_ptr<ITrackingToolQuery> m_ToolLocator;
	misSurfaceLandMarkListType m_SurfaceLandmarkList;
	vtkPoints* m_AllTransformedPoints;
	vtkPoints* m_AllPrimeryCapturedPoints;
	std::shared_ptr<misToolData> m_TempraryTool;
	SurfaceRegistrationDataStrct m_SurfaceRegistrationData;
	double m_LastLandmarkDistanseToSurface{};
	bool m_LastCapturedPointValidity{};
	bool m_LastSoundAlertStatus{};
	double m_LastAutoCaptureLandmarkValue{};
	double m_MaxPermitedErrorForCapturingSurfaceLandmark;
	bool m_PlayAutoCapturingSound{};
	bool m_PlayDistanceSoundToSurface{};
	double m_MaxPermittedErrorForSLCapDefault;
	double m_LastUsedThreshold{};
	bool m_UseAutoMaxPermittedError;
	misToolFixationAnalysis* m_AutomaticCapturelandmark;
	CurrentSubSequenseStateStrct  m_TrackingState;
	std::shared_ptr<misSurfaceRepresentation> m_visibleSurface;
	std::shared_ptr<misSurfaceRepresentation> m_SourcePointSurface;
	misDatasetManager* m_pDataManger;
	std::shared_ptr<IImage> m_pImage;
	vtkPolyData* m_SurfaceRegistartionPolyData;
	misIterativeClosestPointTransform* m_SurfaceTransformCalculator;
	std::vector<std::shared_ptr<misSurfaceRepresentation>> m_LandmarkSpherResult;

	// Note: Create on landmark list in registration manger and pass it to all subsequence only misRegistrationManager is 
	// responsible for deleting it, refactor in future to pass value to subsequences 
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_pLandmarkList;
	double m_NearestLandmarkDistance{};
	std::shared_ptr<ISimpleDataPackage> m_TemporaryPackage;
	bool m_ReadPolyDataFromFile;
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> m_RenderingTools;
	std::shared_ptr<const ITransform> m_PreviousRegistrationTransform;
	std::string m_ReferenceToolUid;	// UID of the reference tracking tool used for surface registration.

	// Logger for registration results
	misReportRegistrationResults m_RegisrationReport;

	//report file path
	const std::string m_ReportFileName;
	std::map<std::shared_ptr<const ITrackingTool>, std::shared_ptr<misTrackingToolMarkerReporter>> m_ToolVisibiltyReports;
	std::shared_ptr<ISurfaceRegistrationUIAdapter> m_SurfaceRegUiADapter;
	std::shared_ptr<misTrackingStateReporter> m_Reporter;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IViewingTypeColormapSelector> m_ViewingTypeColormapSelector;
};
