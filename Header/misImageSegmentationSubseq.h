#pragma once

#include "misAnalysisStudioEvents.h"

#include "misBoneSkineVolume.h"
#include "misColormapResult.h"
#include "misEventFromGui.h"
#include "misMultiViewSubSequence.h"
#include "misObjectPropertiesStruct.h"
#include "misRemoveHeadRestAlgoritm.h"
#include "misSurfaceSegmentation.h"
#include "ICompeleteImageContainedPolydataDependensiesStrct.h"
#include "ISegmentedObjectNameGenerator.h"
#include "VisibilityManagement.h"
#include "IScrewPlanView.h"
#include "ICreateSkinFilledVolume.h"
#include "IRemoveHeadRest.h"
#include "IApplySubSegStatesEventToGUI.h"

class misDatasetManager;
class  misCompeleteImageContainedPolydataDependensiesStrct;

class  misImageSegmentationSubSeq : public misMultiViewSubSequence
{
public:
	misImageSegmentationSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer, std::shared_ptr<misSoftwareInformation> softwareInformation);
	misImageSegmentationSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer,
		 std::shared_ptr<misRegionGrowing> regionGrowin, std::shared_ptr<misSoftwareInformation> softwareInformation);

	void StartSegmentation(misSimplePointListType tBGSeedList, misSimplePointListType tFGSeedList);
	void StartSegmentation(misSimplePointListType tBGSeedList,
		misSimplePointListType tFGSeedList, double* roi);
	static void StartSegmentationThread(misImageSegmentationSubSeq* thisclass);
	void SendObjectPropertiesToGUI(misShort3DModelViewingStrct polydataStr);
	void RealseAllResources();
	void BGSeedCaptureEnable();
	void FGSeedCaptureEnable();
	void AddAllDatasToDataSetManager();
	void UpdateStatus(long long int puls);
	void UpdateSegmentation();
	void UpdateSettingFromAppSetting();
	void OnSelected();
	bool ProcessRequest(misGUIEvent* pEvent);
	double GetCurrentSegmentedObjectThrehsold() const { return m_CurrentSegmentedObjectThrehsold; }
	void SetCurrentSegmentedObjectThrehsold(double val) { m_CurrentSegmentedObjectThrehsold = val; }
	bool SetSegmentedObjectType(mis3DModelTypes modelType);
	misEventListTypedef GetEventToGui();
	void ShowCurrentPackage(std::shared_ptr<ISimpleDataPackage>, bool resetZoom);
	bool m_UseThreadForSegmentation;
	ApproachAndModelInformationStrct GetCurrentObjectProperties() const;
	void Leave();
	void DenySegmentation();
	void SetModeAddFGSeed();
	void SetModeAddBgSeeds();
	void StartSegmentation();
	void UpdateHeadRestRenderingBasedOnNormalizedThreshold(double norThreshold);
	double GetPreviousHeadRestRenderingBasedOnNormalizedThreshold(misVolumeViewingTypes ObjectVolumeViewing) ;

	void SetRemoveHeadRestState();
	void SetROI();
	bool ApplyRemoveHeadRest();
	void SeedSelectionInRemoveHeadRest();

	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);

	template <class EventType>
	void InvokeUnloadedEvent();

	void Initialize();
	void UpdatePackageList();
	void UpdateSelectedItemInTree();
	void StartThresholdBasedSegmenttaion();
	void UpdateObjectProperties();
	void FGSeedListNotification();
	void BGSeedListNotification();
	void ResetSegmentation();
	void SetSeedBasedNormalizedThreshold(double normalizedThreshld);
	void SetThresholdBasedNormalizedThreshold(double normalizedThreshld);
	void UpdateVolumeRedeingSceneBasedOnNormalizedThreshold(double normalizedThreshold);
	void UpdateVolumeThresholdSliderInGUI(double sliderValue);
	void UpdateHeadRestThresholdSliderInGUI(double sliderValue);
	void DeleteSeeds();
	std::shared_ptr<misCompeleteImageContainedPolydataDependensiesStrct> GenerateImageContained();
	void ReplaceToExistingImageContained(vtkImageData* segmentedImage);
	void SetCurrentObjectProperties(misUID newSegmentedID);
	void MergeImageContainedPolyDataRepresentation();
	void PresentSegmentedObject();
	void RemoveROI();
	void SetROIDeactive();
	void SetRoiWidgetActivation(bool activation);
	void SetROIActive();
	void ResetHeadRest();
	void SeedUpdateInRemoveHeadRest();
	void Redo();
	void TaskOnLeave();
	void Render();
	void UpdateCurrentPacakge(std::string packageUid);
	void CompleteProcess(itk::Object *caller, const itk::EventObject& pEvent);
	void SetImagesToInitialPoint();
	void ShowNewPackage(misUID newPackageUID);
	void UpdateDependecies();
	void ShowSelectedItem();
	void SetUpdateVolumeFlag(bool val);
	void CheckFlyZone();
	void UpdateMargin(double MarginValue);
	void ApplyColormap(misColormapResult* colormapEvent);
	vtkSmartPointer<vtkImageData> ApplyMarginToImage(std::shared_ptr<misCompeleteImageContainedPolydataDependensiesStrct> currentImageContained,
		double MarginValue);
	bool AcceptSegmentation();
	void CalculateAndPassHistogram(misUID packageUID);
	std::map<int, int> GetHistogram(std::shared_ptr<IImage> image);
	misVolumeViewingTypes GetVolumeViewingtype();
	bool AcceptColormap();
	bool DenyColormap();
	void SetObjectInitialName(mis3DModelTypes ObjectType);

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	misUID m_PackageUID;
	misUID m_imageUID;
	misUID m_NewObjectUID;
	std::shared_ptr<IImage> m_MainImage;
	std::map<std::shared_ptr<IImage>, std::shared_ptr<IBoneSkineVolume>> m_SkinBoneCompositer;
	std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> m_imageContainedStructData;
	misObjectVisibilityMap	m_OriginalSegmentMap;
	std::string m_NewObjectName;
	misObjectProperties m_ObjectProperties;
	ApproachAndModelInformationStrct m_CurrentObjectProperties;
	misDatasetManager* m_DataSetManger;
	HANDLE m_mutex;
	std::shared_ptr<misSurfaceSegmentation> m_SurfaceSegmentation;
	misImageStatus m_ImageStatus;
	double m_CurrentSegmentedObjectThrehsold;
	std::vector<vtkTextActor*> FlyZoneStatusText;
	misVolumeViewingTypes m_CurrentViewingType;
	misROI m_ROI;
	std::shared_ptr<misRegionGrowing> m_RegionGrowing;
	std::shared_ptr<TransFuncIntensity> m_TransferFunction;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<parcast::ISegmentedObjectNameGenerator> m_NameGenerator;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
		std::shared_ptr<IRemoveHeadRest>  m_RemoveHeadRest ;
	std::shared_ptr<IApplySubSegStatesEventToGUI>  m_ApplySubSegStatesEventToGUI;

};