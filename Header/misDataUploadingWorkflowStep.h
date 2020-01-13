#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "IWorkflowStep.h"
#include "misCineInformation.h"
#include "misDataBaseManager.h"
#include "misImage.h"
#include "misVolumeSlicer.h"
#include "misPlanarRepresentation.h"
#include "misSolutionProperty.h"
#include "misDataProdecureEnum.h"
#include "misDICOMImageLoader.h"
#include "mis3DViewer.h"

class misDataUploadingWorkflowStep : public IWorkflowStep
{
public:	
	enum Status
	{
		Uninitialized,
		Initializing,
		Initialized,
		AnalyzingDirectory,
		LoadingSeries,
		PreviewRunningGUI,
		LeaveNoEditNopreviewNo,
		LeaveNoEditNopreviewYes,
		LeaveNoEditYespreviewYes,
		LeaveNoEditYespreviewNo,
		LeaveYesEditYespreviewNo,
		LeaveYesEditYespreviewYes,
		UploadedImage,
		CompletedTask
	};

	MIS_HAS_EVENTS_IMPLEMENTATION_WITHOUT_BASE;

	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(DicomTreeList, const PatientsContainerViewingTypdef& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(LoadedSeriesSelected, bool params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(UpdateDicomProperties, const misDicomDataViewingProperties& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(LoadedDicomList, const ImageViewingListTypedef& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(SetSliderProperty, double params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(RequestSetPatientProperties, const misPatientProperties& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(SetPatientProperties, const misPatientProperties& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(UpdateSnapShotFolderAddress, const std::string& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(PatientUploadingStatus, bool params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(CurrentSliceChanged, const sliderInfoStruct& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(AskForUploadingWithDifficulties, const misImgeProblemList& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(ImageProblemReport, const std::string& params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(CurrentStatusChanged, Status lastStatus, Status currentStatus);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(DisableAllSliders, void);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(RefreshGUI, void);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(OpenWaitingBarEventCore, const std::string& title, const std::string message);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(CloseNonThreadingWaitingBar, void);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(SetWaitingBarValue, double params);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(ClearLists, void);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(OpenNonThreadingWaitingBar, const std::string& title, const std::string message,
		const std::string& cancelFunctionName, bool automaticProgressBar);
	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(UpdateNonthreadingWaitingBarValue, double params);

	misDataUploadingWorkflowStep(const std::string& stepID, 
		std::shared_ptr<misDataBaseManager> databaseManager, 
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, 
		std::shared_ptr<ISettingsContainer> applicationSettings, misDatasetManager* datasetManager);

	// IWorkflowStep interface:
	virtual void LeaveWorkflowStep() override;
	virtual void EnterWorkflowStep() override;
	virtual std::string GetStepId() const override;
	virtual void UpdateStatus() override;
	
	virtual Status GetCurrentStatus() const;

	// Sets the native window handle where the image should be rendered and displayed.
	void SetWindowHandle(void* handle);

	bool CancelBrowseAndAalysisFolder();
	bool CancelReadingSerie();
	bool DicomDirRead(const std::string& AnalyzeDirectory);
	bool TreeviewStudyClicked(const misImageIndexData& params);
	bool TreeviewPatientClicked(const misImageIndexData& params);
	bool TreeviewSeriesClicked(const misImageIndexData& index);
	bool ForceToUploadWithProblem();
	bool PrevSeriIntervalChanged(int interval);
	bool PrevSeriStopRequest();
	bool PrevSeriButtonClicked(misCineDirection direction);
	bool UploadSeries();
	bool EditButtonClicked(const misPatientProperties& params);
	bool PatientTreeDeleteClick(const misUID& params);
	bool PatientTreePropClick(const misImageViewingItemsStruct& params);
	bool LoadedSeriClick(const misUID& params);

private:
	// Changes the current internal workflow step status and raises the corresponding event.
	void ChangeStatus(Status newStatus);

	void Initialize();
	void UpdateGUIContents();
	void UpdatePatientPropertiesInGUI();
	void UpdateGUIState();

	void ConvertImageInCaseFloatOrDouble();
	bool UpadatedClassImagePointer(misUID newPrimeryUID);
	void UpdateCineInformation(misUID newUID,misCineDirection cineDirection);
	void PrevSeriButtonClickedProcessing(misCineDirection cineDirection);
	void Render();
	void IsThereAnyPatientProcessing();
	void AttempToUploadProcessing();
	void MakeNewPatientProcessing();
	void UploadImage();
	void SetImageName();
	void UpdateImageName(misImageViewingItemsStruct imageStr);
	void UpdateStatusWhileProcessingTreePatient();
	void UpdateStatusWhileProcessingSerie();
	void UpdateTreePatientListInGUI();
	void OnEndingSerieProcessingTask();
	bool EvaluateImage();
	void ShowSelectedImage();
	void RaiseCurrentStatusChangedIfNeeded();
	void RequestStopPrevSeri();
	void RequestChangePrevSeriInterval(int interval);
	void RealseAllResources();
	void ReleasTempImages();
	void ClearGUILists();
	std::vector<mis3DViewer*> GetAllViewers();
	bool SeriesAlreadyProcessed( misImageIndexData imageIndexes );
	void SetSolotionProperty( std::shared_ptr<misSolutionProperty> val );
	std::shared_ptr<misImage> GetLoadedImage() const;
	void SetLoadedImage( std::shared_ptr<misImage> val );
	std::shared_ptr<misSolutionProperty> GetSolotionProperty() const;

	void ShowImage(std::shared_ptr<misImage> image);


	int m_LastImageHandle;
	std::map< int, std::shared_ptr<misImage> > m_LoadedImagesMap;
	Status m_CurrentStatus;
	void* m_WindowHandle;
	std::string m_StepId;
	std::shared_ptr<misVolumeSlicer> m_ImageViewer;
	std::shared_ptr<ISettingsContainer> m_ApplicationSettings;
	misPlanarRepresentation::Pointer m_2DRepresentation;
	misCineInformation m_cineInfo;
	bool m_isPreviewStart;
	misUID               m_lastUID;	
	int	 m_CTCounter;
	int	 m_MRCounter;
	std::shared_ptr<misImage> m_LoadedImage;	// loaded image created by m_DICOMImageLoader
	misDatasetManager* m_DataSetManager;
	std::shared_ptr<misSolutionProperty> m_SolotionProperty;
	DataUploadingStatuse m_SubTabStatuses;
	bool m_CancelRequest;
	ImageListTypedef				m_TempImages;	// A list of all the image retrieved from m_DICOMImageLoader
	misDICOMImageLoader				m_DICOMImageLoader;
	bool m_StatusUpdateRequired;	// Checked by UpdateStatus() to determine whether an actual update is required.
	PatientsContainerViewingTypdef  m_PatientTree;	// Retrieved from m_DICOMImageLoader.
};