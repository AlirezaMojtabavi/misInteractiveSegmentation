#pragma once

#include "misCineInformation.h"
#include "misDICOMImageLoader.h"
#include "misDatasetManager.h"
#include "misImageIndexData.h"
#include "IVolumeSlicer.h"
#include "misMacros.h"
#include "misMultiViewSubSequence.h"
#include "misStrctDicomIO.h"
#include "misSubSequence.h"
#include "CorrectImageDirectionCalculator.h"
#include "IVolumeThreshold.h"
#include "IVolumeThresholdSliderRangeUpdater.h"


class IPackage2DDataRenderingAdapter;
class misDIRReader;
class IDataUploadingUIADapter;
class ISubsequenceLayout;
class IImage;

typedef std::vector< std::shared_ptr<IImage>> ImageListTypedef;

struct SerieProcessingMsg
{
	itk::LoggerBase::PriorityLevelType	priorityLevel;
	std::string							msg;

	void Reset()
	{
		msg = "";
		priorityLevel = itk::LoggerBase::NOTSET;
	}

	SerieProcessingMsg()
	{
		Reset();
	}
};

class  misDataSetUploadinSubSeq : public misMultiViewSubSequence
{
public:

	misDataSetUploadinSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer,  std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager,
		misApplicationType applicationType, std::shared_ptr<misSoftwareInformation> softwareInformation);

	misCreateVariableWithBooleanMacro(UseThreadForFolderAnalysis);
	misGetMacro(parent, misOldObject*);
	friend  class misIntegrationTestApplication;
	bool ProcessRequest(misGUIEvent* pEvent) override;
	void Render();
	// Updates the GUI status including progress bar, displays errors if any, and reports operation completion.
	void UpdateStatus(long long int pulse);
	void RequestSetParent(misOldObject*  obj) { this->m_parent = obj; }
	std::vector<std::shared_ptr<I3DViewer>>  GetAllViewers() override;	//override
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	virtual misEventListTypedef GetEventToGui();
	std::shared_ptr<misSolutionProperty> GetSolotionProperty() const;
	void SetSolotionProperty(std::shared_ptr<misSolutionProperty> val);
	std::shared_ptr<IImage> GetLoadedImage() const;
	void SetLoadedImage(std::shared_ptr<IImage> val);
	void ShowImage(std::shared_ptr<IImage> image);

private:
	void RequestInitializeGUI(std::shared_ptr<ISubsequenceLayout>    dataTab);
	void ConvertImageInCaseFloatOrDouble();
	void IsThereAnyPatientProcessing();
	void AttempToUploadProcessing();
	void UploadImage();
	void MakeNewPatientProcessing();
	void InitialeGuiProcessing();
	void UpdateGUIState();
	bool UpadatedClassImagePointer(misUID newPrimeryUID);
	void UpdateSettingFromAppSetting();
	void CloseProgressbar();
	void SetWaitingBarValue(double prgbarVal);
	void RealseAllResources();
	void ClearGUILists();
	void ResetSetting();
	void ReleasTempImages();
	void TaskOnLeave();
	void OnSelected();
	void UpdateGUIContents();
	void UpdatePatientPropertiesInGUI();
	void UpdateImageName(misImageViewingItemsStruct imageStr);
	bool SeriesAlreadyProcessed(misImageIndexData imageIndexes);
	void UpdateTreePatientListInGUI();
	void DeleteImage(std::string imageUID, std::shared_ptr<IImage> image);
	// Updates GUI data when building tree operation is in progress. Called by UpdateStatus()
	void UpdateStatusWhileProcessingTreePatient();
	void SetCorrectImageOrientation();
	// Updates GUI data when series processing is in progress. Called by UpdateStatus()
	void UpdateStatusWhileProcessingSerie();
	// Set image name based on its modality and order of series clicked.
	void SetImageName();
	// Performs finalization tasks (resetting internal class state, ...) when series processing is finished.
	void OnEndingSerieProcessingTask();
	bool EvaluateImage();

	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);

	template <class EventType>
	void InvokeUnloadedEvent();
 	void SetMRThreshold(const std::string& MRProtocolName);

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	int	 m_CTCounter;
	int	 m_MRCounter;
	bool m_CancelRequest;	// Determines whether the user has pressed the Cancel button.
	bool m_StatusUpdateRequired;	// Checked by UpdateStatus() to determine whether an actual update is required.
	misUID  m_lastUID;
	misDatasetManager*   m_DataSetManger;
	DataUploadingStatuse m_SubTabStatuses;
	misOldObject*		 m_parent;
	std::shared_ptr<IImage> m_LoadedImage;	// loaded image created by m_DICOMImageLoader
	ImageListTypedef	m_TempImages;	// A list of all the image retrieved from m_DICOMImageLoader
	std::shared_ptr<misPlanarRepresentation> m_2DRepresentation;
	misDICOMImageLoader	 m_DICOMImageLoader;
	PatientsContainerViewingTypdef  m_PatientTree;	// Retrieved from m_DICOMImageLoader.
	std::shared_ptr<misSolutionProperty> m_SolotionProperty;
	misApplicationSetting *m_AppSetting;
	std::shared_ptr<IDataUploadingUIADapter> m_UIAdapter;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<ISimpleDataPackage> m_WorkingPackage;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<parcast::IVolumeThreshold> m_VolumeThreshold;
	std::shared_ptr<parcast::IVolumeThresholdSliderRangeUpdater> m_ThresholdSliderRangeUpdater;

};
